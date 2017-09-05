// byte order (network-byte-order <-> host-byte-order) conversions
// network byte order is big-endian, therefore we can use be*toh und htobe* methods


#ifndef SECUREMEMORY_CONVERSIONS_H
#define SECUREMEMORY_CONVERSIONS_H

#include <algorithm>

extern "C" {
    #include "_conversions_crossplatform.h"
}

/**
 * Converts an uint8_t from network to host byte order
 * @param v Value to convert to network byte order
 * @return v in host byte order
 */
inline uint8_t ntoh_uint8_t(uint8_t v) {
    // a byte is a byte, no need to swap
    return v;
}
inline int8_t ntoh_int8_t(int8_t v) {
    // a byte is a byte, no need to swap
    return v;
}

/**
 * Converts an uint16_t from network to host byte order
 * @param v Value to convert to network byte order
 * @return v in host byte order
 */
inline uint16_t ntoh_uint16_t(uint16_t v) {
    return be16toh(v);
}
inline int16_t ntoh_int16_t(int16_t v) {
    return be16toh(v);
}

/**
 * Converts an uint32_t from network to host byte order
 * @param v Value to convert to network byte order
 * @return v in host byte order
 */
inline uint32_t ntoh_uint32_t(uint32_t v) {
    return be32toh(v);
}
inline int32_t ntoh_int32_t(int32_t v) {
    return be32toh(v);
}

/**
 * Converts an uint64_t from network to host byte order
 * @param v Value to convert to network byte order
 * @return v in host byte order
 */
inline uint64_t ntoh_uint64_t(uint64_t v) {
    return be64toh(v);
}
inline int64_t ntoh_int64_t(int64_t v) {
    return be64toh(v);
}

/**
 * Converts an uint8_t from host to network byte order
 * @param v Value to convert to host byte order
 * @return v in network byte order
 */
inline uint8_t hton_uint8_t(uint8_t v) {
    // a byte is a byte, no need to swap
    return v;
}
inline int8_t hton_int8_t(int8_t v) {
    // a byte is a byte, no need to swap
    return v;
}

/**
 * Converts an uint16_t from host to network byte order
 * @param v Value to convert to host byte order
 * @return v in network byte order
 */
inline uint16_t hton_uint16_t(uint16_t v) {
    return htobe16(v);
}
inline int16_t hton_int16_t(int16_t v) {
    return htobe16(v);
}

/**
 * Converts an uint32_t from host to network byte order
 * @param v Value to convert to host byte order
 * @return v in network byte order
 */
inline uint32_t hton_uint32_t(uint32_t v) {
    return htobe32(v);
}
inline int32_t hton_int32_t(int32_t v) {
    return htobe32(v);
}

/**
 * Converts an uint64_t from host to network byte order
 * @param v Value to convert to host byte order
 * @return v in network byte order
 */
inline uint64_t hton_uint64_t(uint64_t v) {
    return htobe64(v);
}
inline int64_t hton_int64_t(int64_t v) {
    return htobe64(v);
}

// TODO documentation

template <typename T>
T bswap(T v) {
    const uint8_t bytes = sizeof(T);
    T ret;
    for (uint8_t i=0; i<bytes; ++i)
        reinterpret_cast<uint8_t*>(&ret)[bytes-i-1] = ((reinterpret_cast<uint8_t*>(&v)[i]));

    return ret;
}

template <>
inline uint8_t bswap(uint8_t v) {
    return v;
}

template <>
inline uint16_t bswap(uint16_t v) {
    return __bswap_16(v);
}

template <>
inline uint32_t bswap(uint32_t v) {
    return __bswap_32(v);
}

template <>
inline uint64_t bswap(uint64_t v) {
    return __bswap_64(v);
}

template <typename T>
T _bswap_float_double(T v) {
    switch (sizeof(v)) {
        case sizeof(uint32_t): {
            uint32_t dst;

            char *src = reinterpret_cast<char *>(&v);
            std::copy(src, src+sizeof(uint32_t), reinterpret_cast<char*>(&dst));
            dst = bswap(dst);

            src = reinterpret_cast<char *>(&dst);
            std::copy(src, src+sizeof(uint32_t), reinterpret_cast<char*>(&v));

            return v;
        }
        case sizeof(uint64_t): {
            uint64_t dst;

            char *src = reinterpret_cast<char *>(&v);
            std::copy(src, src+sizeof(uint64_t), reinterpret_cast<char*>(&dst));
            dst = bswap(dst);

            src = reinterpret_cast<char *>(&dst);
            std::copy(src, src+sizeof(uint64_t), reinterpret_cast<char*>(&v));

            return v;
        }
        default:
            return bswap(v);
    }
}

template <>
inline float bswap(float v) {
    return _bswap_float_double(v);
}


template <>
inline double bswap(double v) {
    return _bswap_float_double(v);
}



template<typename T>
inline T hton(T v) {
#if BYTE_ORDER == LITTLE_ENDIAN
        return bswap(v);
#else
        return v;
#endif
}

template<typename T>
inline T ntoh(T v) {
#if BYTE_ORDER == LITTLE_ENDIAN
    return bswap(v);
#else
    return v;
#endif
}

#endif //SECUREMEMORY_CONVERSIONS_H
