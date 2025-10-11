/* Copyright (C) 2025 Björn Esser <besser82@fedoraproject.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "crypt-port.h"

#if INCLUDE_bcrypt_x

#include <errno.h>
#include <stdio.h>

int
main (void)
{
  char *retval;

  errno = 0;
  retval = crypt_gensalt ("$2x$", 0, NULL, 0);

  if (retval || errno != EINVAL)
    {
      fprintf (stderr, "gensalt: expected \"NULL\", got \"%s\" "
                       "with errno == %i, instead of %i.\n",
               retval ? retval : "NULL", errno, EINVAL);

      return 1;
    }

  return 0;
}

#else

int
main (void)
{
  return 77; /* UNSUPPORTED */
}

#endif /* INCLUDE_bcrypt_x */
