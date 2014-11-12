#define FD_SETSIZE 256

#ifdef __MINGW32__
#include <winsock2.h>
#else
#ifdef __MINGW64__
#include <winsock2.h>
#else
#include <WinSock2.h>
#endif
#endif

#include <stdlib.h>
#include <errno.h>
#include "websock-w32.h"

PFNWSAPOLL poll = NULL;

INT WSAAPI emulated_poll(LPWSAPOLLFD fdarray, ULONG nfds, INT timeout)
{
	fd_set readfds;
	fd_set writefds;
	struct timeval tv;
	struct timeval *ptv = &tv;
	SOCKET max_socket = 0;
	ULONG n = 0;
	int waiting;
	int pending = 0;
	WSAPOLLFD * poll_fd = fdarray;

	if (NULL == fdarray) {
		errno = EFAULT;
		return -1;
	}

	FD_ZERO(&readfds);
	FD_ZERO(&writefds);

	tv.tv_sec = timeout / 1000;
	tv.tv_usec = (timeout % 1000) * 1000;

	if (timeout < 0)
		ptv = NULL;

	while (n < nfds) {

		poll_fd->revents = 0;

		if (poll_fd->fd < 0 || !poll_fd->events)
			goto skip1;

		if (max_socket < poll_fd->fd)
			max_socket = poll_fd->fd;

		if (poll_fd->events & POLLIN)
			FD_SET(poll_fd->fd, &readfds);

		if (poll_fd->events & POLLOUT)
			FD_SET(poll_fd->fd, &writefds);
skip1:
		poll_fd++;
		n++;
	}

	waiting = select((int)max_socket + 1, &readfds, &writefds, NULL, ptv);

	if (waiting <= 0)
		return waiting;

	poll_fd = fdarray;

	while (waiting && nfds--) {

		if (!poll_fd->events)
			goto skip2;

		if (poll_fd->fd <= 0) {
			poll_fd->revents = POLLNVAL;
			goto skip2;
		}

		if (FD_ISSET(poll_fd->fd, &readfds)) {

			/* defer POLLHUP / error detect to false read attempt */

			poll_fd->revents |= POLLIN;
			waiting--;
		}

		if (FD_ISSET(poll_fd->fd, &writefds)) {

			poll_fd->revents |= poll_fd->events & POLLOUT;
			waiting--;
		}

		if (poll_fd->revents)
			pending++;

skip2:
		poll_fd++;
	}

	return pending;
}
