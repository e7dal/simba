/**
 * @file queue.c
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2014-2015, Erik Moqvist
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERQUEUETABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Simba project.
 */

#include "simba.h"

#define BUFFER_SIZE(buffer_p) \
    ((buffer_p)->end_p - (buffer_p)->begin_p - 1)
#define BUFFER_USED_UNTIL_END(buffer_p) \
    ((buffer_p)->end_p - (buffer_p)->read_p)
#define WRITER_SIZE(queue_p) \
    ((queue_p->base.writer_p != NULL) * queue_p->left)
#define BUFFER_UNUSED_UNTIL_END(buffer_p) \
    ((buffer_p)->end_p - (buffer_p)->write_p)
#define BUFFER_UNUSED(buffer_p) \
    (BUFFER_SIZE(buffer_p) - get_buffer_used(buffer_p))

static inline size_t get_buffer_used(struct queue_buffer_t *buffer_p)
{
    if (buffer_p->begin_p == NULL) {
        return (0);
    }

    if (buffer_p->write_p == buffer_p->read_p) {
        return (0);
    } else if (buffer_p->write_p > buffer_p->read_p) {
        return (buffer_p->write_p - buffer_p->read_p);
    } else {
        return ((buffer_p->end_p - buffer_p->begin_p)
                - (buffer_p->read_p - buffer_p->write_p));
    }
}

int queue_init(struct queue_t *self_p,
               void *buf_p,
               size_t size)
{
    chan_init(&self_p->base,
              (ssize_t (*)(void *, void *, size_t))queue_read,
              (ssize_t (*)(void *, const void *, size_t))queue_write,
              (size_t (*)(void *))queue_size);

    self_p->buffer.begin_p = buf_p;
    self_p->buffer.read_p = buf_p;
    self_p->buffer.write_p = buf_p;
    self_p->buffer.end_p = &((char*)buf_p)[size];

    self_p->buf_p = NULL;
    self_p->size = 0;
    self_p->left = 0;

    return (0);
}

ssize_t queue_read(struct queue_t *self_p, void *buf_p, size_t size)
{
    size_t left, n, buffer_used_until_end, buffer_used;
    char *cbuf_p;

    left = size;
    cbuf_p = buf_p;

    sys_lock();

    /* Copy data from queue buffer. */
    if (self_p->buffer.begin_p != NULL) {
        buffer_used = get_buffer_used(&self_p->buffer);

        if (left < buffer_used) {
            n = left;
        } else {
            n = buffer_used;
        }

        buffer_used_until_end = BUFFER_USED_UNTIL_END(&self_p->buffer);

        if (n <= buffer_used_until_end) {
            memcpy(cbuf_p, self_p->buffer.read_p, n);
            self_p->buffer.read_p += n;
        } else {
            memcpy(cbuf_p, self_p->buffer.read_p, buffer_used_until_end);
            memcpy(cbuf_p + buffer_used_until_end,
                   self_p->buffer.begin_p,
                   (n - buffer_used_until_end));
            self_p->buffer.read_p = self_p->buffer.begin_p;
            self_p->buffer.read_p += (n - buffer_used_until_end);
        }

        cbuf_p += n;
        left -= n;
    }

    /* Copy data from the writer, if one is present. */
    if (self_p->base.writer_p != NULL) {
        if (left < self_p->left) {
            n = left;
        } else {
            n = self_p->left;
        }

        memcpy(cbuf_p, self_p->buf_p, n);
        self_p->buf_p += n;
        self_p->left -= n;
        cbuf_p += n;
        left -= n;

        /* Writer buffer empty. */
        if (self_p->left == 0) {
            /* Wake the writer. */
            thrd_resume_irq(self_p->base.writer_p, 0);
            self_p->base.writer_p = NULL;
        }
    }

    /* Suspend this thread if more data should be read. */
    if (left > 0) {
        /* The writer writes the remaining data to the reader buffer. */
        self_p->base.reader_p = thrd_self();
        self_p->buf_p = cbuf_p;
        self_p->left = left;

        thrd_suspend_irq(NULL);
    }

    sys_unlock();

    return (size);
}

ssize_t queue_write(struct queue_t *self_p,
                    const void *buf_p,
                    size_t size)
{
    size_t left;
    const char *cbuf_p;

    left = size;
    cbuf_p = buf_p;

    sys_lock();

    left -= queue_write_irq(self_p, cbuf_p, size);

    /* The writer writes the remaining data. */
    if (left > 0) {
        cbuf_p += (size - left);
        self_p->base.writer_p = thrd_self();
        self_p->buf_p = (void *)cbuf_p;
        self_p->left = left;

        thrd_suspend_irq(NULL);
    }

    sys_unlock();

    return (size);
}

ssize_t queue_write_irq(struct queue_t *self_p,
                        const void *buf_p,
                        size_t size)
{
    size_t n, left;
    size_t buffer_unused_until_end, buffer_unused;
    const char *cbuf_p;

    left = size;
    cbuf_p = buf_p;

    if (chan_is_polled_irq(&self_p->base)) {
        thrd_resume_irq(self_p->base.reader_p, 0);
        self_p->base.reader_p = NULL;
    }

    /* Copy data to the reader, if one is present. */
    if (self_p->base.reader_p != NULL) {
        if (left < self_p->left) {
            n = left;
        } else {
            n = self_p->left;
        }
        
        memcpy(self_p->buf_p, cbuf_p, n);

        self_p->buf_p += n;
        self_p->left -= n;
        cbuf_p += n;
        left -= n;

        /* Read buffer full. */
        if (self_p->left == 0) {
            /* Wake the reader. */
            thrd_resume_irq(self_p->base.reader_p, 0);
            self_p->base.reader_p = NULL;
        }
    }

    if ((left > 0) && (self_p->buffer.begin_p != NULL)) {
        buffer_unused = BUFFER_UNUSED(&self_p->buffer);

        if (left < buffer_unused) {
            n = left;
        } else {
            n = buffer_unused;
        }

        buffer_unused_until_end = BUFFER_UNUSED_UNTIL_END(&self_p->buffer);

        if (n <= buffer_unused_until_end) {
            memcpy(self_p->buffer.write_p, cbuf_p, n);
            self_p->buffer.write_p += n;
        } else {
            memcpy(self_p->buffer.write_p, cbuf_p, buffer_unused_until_end);
            memcpy(self_p->buffer.begin_p,
                   cbuf_p + buffer_unused_until_end,
                   (n - buffer_unused_until_end));
            self_p->buffer.write_p = self_p->buffer.begin_p;
            self_p->buffer.write_p += (n - buffer_unused_until_end);
        }

        left -= n;
    }

    return (size - left);
}

ssize_t queue_size(struct queue_t *self_p)
{
    return (get_buffer_used(&self_p->buffer) + WRITER_SIZE(self_p));
}
