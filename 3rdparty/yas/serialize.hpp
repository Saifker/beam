
// Copyright (c) 2010-2018 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef __yas__serialize_hpp
#define __yas__serialize_hpp

#include <yas/binary_oarchive.hpp>
#include <yas/binary_iarchive.hpp>
#include <yas/text_oarchive.hpp>
#include <yas/text_iarchive.hpp>
#include <yas/json_oarchive.hpp>
#include <yas/json_iarchive.hpp>
#include <yas/mem_streams.hpp>
#include <yas/file_streams.hpp>

namespace yas {

/***************************************************************************/

template<std::size_t F, typename ...Types>
typename std::enable_if<
     (F & yas::mem) && (F & yas::binary)
    ,yas::shared_buffer
>::type
save(Types &&... args) {
    yas::mem_ostream os;
    yas::binary_oarchive<yas::mem_ostream, (F & (~yas::mem))> oa(os);
    oa(std::forward<Types>(args)...);

    return os.get_shared_buffer();
}

template<std::size_t F, typename ...Types>
typename std::enable_if<
     (F & yas::mem) && (F & yas::text)
    ,yas::shared_buffer
>::type
save(Types &&... args) {
    yas::mem_ostream os;
    yas::text_oarchive<yas::mem_ostream, (F & (~yas::mem))> oa(os);
    oa(std::forward<Types>(args)...);

    return os.get_shared_buffer();
}

template<std::size_t F, typename ...Types>
typename std::enable_if<
     (F & yas::mem) && (F & yas::json)
    ,yas::shared_buffer
>::type
save(Types &&... args) {
    yas::mem_ostream os;
    yas::json_oarchive<yas::mem_ostream, (F & (~yas::mem))> oa(os);
    oa(std::forward<Types>(args)...);

    return os.get_shared_buffer();
}

template<std::size_t F, typename ...Types>
typename std::enable_if<
    (F & yas::file) && (F & yas::binary)
>::type
save(const char *fname, Types &&... args) {
    yas::file_ostream os(fname);
    yas::binary_oarchive<yas::file_ostream, (F & (~yas::file))> oa(os);
    oa(std::forward<Types>(args)...);
}

template<std::size_t F, typename ...Types>
typename std::enable_if<
    (F & yas::file) && (F & yas::text)
>::type
save(const char *fname, Types &&... args) {
    yas::file_ostream os(fname);
    yas::text_oarchive<yas::file_ostream, (F & (~yas::file))> oa(os);
    oa(std::forward<Types>(args)...);
}

template<std::size_t F, typename ...Types>
typename std::enable_if<
    (F & yas::file) && (F & yas::json)
>::type
save(const char *fname, Types &&... args) {
    yas::file_ostream os(fname);
    yas::json_oarchive<yas::file_ostream, (F & (~yas::file))> oa(os);
    oa(std::forward<Types>(args)...);
}

/***************************************************************************/

template<std::size_t F, typename Buf, typename ...Types>
typename std::enable_if<
    (F & yas::mem) && (F & yas::binary)
>::type
load(const Buf &buf, Types &&... args) {
    yas::mem_istream is(buf);
    yas::binary_iarchive<yas::mem_istream, (F & (~yas::mem))> ia(is);
    ia(std::forward<Types>(args)...);
}

template<std::size_t F, typename Buf, typename ...Types>
typename std::enable_if<
    (F & yas::mem) && (F & yas::text)
>::type
load(const Buf &buf, Types &&... args) {
    yas::mem_istream is(buf);
    yas::text_iarchive<yas::mem_istream, (F & (~yas::mem))> ia(is);
    ia(std::forward<Types>(args)...);
}

template<std::size_t F, typename Buf, typename ...Types>
typename std::enable_if<
    (F & yas::mem) && (F & yas::json)
>::type
load(const Buf &buf, Types &&... args) {
    yas::mem_istream is(buf);
    yas::json_iarchive<yas::mem_istream, (F & (~yas::mem))> ia(is);
    ia(std::forward<Types>(args)...);
}

template<std::size_t F, typename ...Types>
typename std::enable_if<
    (F & yas::file) && (F & yas::binary)
>::type
load(const char *fname, Types &&... args) {
    yas::file_istream is(fname);
    yas::binary_iarchive<yas::file_istream, (F & (~yas::file))> ia(is);
    ia(std::forward<Types>(args)...);
}

template<std::size_t F, typename ...Types>
typename std::enable_if<
    (F & yas::file) && (F & yas::text)
>::type
load(const char *fname, Types &&... args) {
    yas::file_istream is(fname);
    yas::text_iarchive<yas::file_istream, (F & (~yas::file))> ia(is);
    ia(std::forward<Types>(args)...);
}

template<std::size_t F, typename ...Types>
typename std::enable_if<
    (F & yas::file) && (F & yas::json)
>::type
load(const char *fname, Types &&... args) {
    yas::file_istream is(fname);
    yas::json_iarchive<yas::file_istream, (F & (~yas::file))> ia(is);
    ia(std::forward<Types>(args)...);
}

/***************************************************************************/

} // namespace yas

#endif // __yas__serialize_hpp