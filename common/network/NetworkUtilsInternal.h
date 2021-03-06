/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * NetworkUtilsInternal.h
 * Abstract various network functions.
 * Copyright (C) 2005 Simon Newton
 */

#ifndef COMMON_NETWORK_NETWORKUTILSINTERNAL_H_
#define COMMON_NETWORK_NETWORKUTILSINTERNAL_H_

#if HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_WINSOCK2_H
#define VC_EXTRALEAN
#include <Winsock2.h>
#endif

#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#include <string>

namespace ola {
namespace network {

/**
 * Return the length of a sockaddr
 */
unsigned int SockAddrLen(const struct sockaddr &sa);

}  // namespace network
}  // namespace ola
#endif  // COMMON_NETWORK_NETWORKUTILSINTERNAL_H_
