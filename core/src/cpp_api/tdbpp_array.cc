/**
 * @file  tdbpp_array.cc
 *
 * @author Ravi Gaddipati
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2017 TileDB, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * This file declares the C++ API for TileDB.
 */

#include "tdbpp_context.h"
#include "tdbpp_arraymeta.h"
#include "tdbpp_array.h"
#include "tdbpp_query.h"

std::ostream &operator<<(std::ostream &os, const tdb::Array &array) {
  os << "Array<" << array.context() << ' ' << array.meta() << ">";
  return os;
}

void tdb::Array::create(const tdb::ArrayMetadata &meta) {
  meta.check();
  auto &ctx = _ctx.get();
  _meta = meta;
  ctx.handle_error(tiledb_array_create(ctx, meta._meta.get()));
}

const std::string tdb::Array::name() const {
  return _meta.name();
}

bool tdb::Array::good() const {
  return _meta.good();
}

void tdb::Array::load(const std::string &uri) {
  _meta.load(uri);
}

tdb::Context &tdb::Array::context() {
  return _ctx.get();
}

const tdb::Context &tdb::Array::context() const {
  return _ctx.get();
}

tdb::ArrayMetadata &tdb::Array::meta() {
  return _meta;
}

const tdb::ArrayMetadata &tdb::Array::meta() const {
  return _meta;
}

tdb::Array::Array(const tdb::ArrayMetadata &meta) : _ctx(meta._ctx), _meta(meta) {}

tdb::Query tdb::Array::read() {
  return Query(*this, TILEDB_READ);
}

tdb::Query tdb::Array::write() {
  return Query(*this, TILEDB_WRITE);
}