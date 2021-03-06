/*
 *
 *    Copyright (c) 2019 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *          Utility functions for working with OpenThread.
 */


#ifndef OPENTHREAD_UTILS_H
#define OPENTHREAD_UTILS_H

#include <openthread/thread.h>
#include <openthread/error.h>
#include <openthread/ip6.h>

namespace nl {
namespace Weave {
namespace DeviceLayer {
namespace Internal {

/**
 *  @def WEAVE_CONFIG_OPEN_THREAD_ERROR_MIN
 *
 *  @brief
 *      The base value for OpenThread errors when mapped into the Weave error space.
 */
#ifndef WEAVE_CONFIG_OPEN_THREAD_ERROR_MIN
#define WEAVE_CONFIG_OPEN_THREAD_ERROR_MIN                  9000000
#endif // WEAVE_CONFIG_OPEN_THREAD_ERROR_MIN

/**
 *  @def WEAVE_CONFIG_OPEN_THREAD_ERROR_MAX
 *
 *  @brief
 *      The max value for OpenThread errors when mapped into the Weave error space.
 */
#ifndef WEAVE_CONFIG_OPEN_THREAD_ERROR_MAX
#define WEAVE_CONFIG_OPEN_THREAD_ERROR_MAX                  9000999
#endif // WEAVE_CONFIG_OPEN_THREAD_ERROR_MAX


extern WEAVE_ERROR MapOpenThreadError(otError otErr);
extern void RegisterOpenThreadErrorFormatter(void);
extern void LogOpenThreadStateChange(otInstance * otInst, uint32_t flags);
extern void LogOpenThreadPacket(const char * titleStr, otMessage * pkt);
extern bool IsOpenThreadMeshLocalAddress(otInstance * otInst, const IPAddress & addr);
extern const char * OpenThreadRoleToStr(otDeviceRole role);

inline otIp6Address ToOpenThreadIP6Address(const IPAddress & addr)
{
    otIp6Address otAddr;
    memcpy(otAddr.mFields.m32, addr.Addr, sizeof(otAddr.mFields.m32));
    return otAddr;
}

inline IPAddress ToIPAddress(const otIp6Address & otAddr)
{
    IPAddress addr;
    memcpy(addr.Addr, otAddr.mFields.m32, sizeof(addr.Addr));
    return addr;
}

inline IPPrefix ToIPPrefix(const otIp6Prefix & otPrefix)
{
    IPPrefix prefix;
    prefix.IPAddr = ToIPAddress(otPrefix.mPrefix);
    prefix.Length = otPrefix.mLength;
    return prefix;
}

} // namespace Internal
} // namespace DeviceLayer
} // namespace Weave
} // namespace nl

#endif // OPENTHREAD_UTILS_H
