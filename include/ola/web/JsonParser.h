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
 * JsonParser.h
 * A class for Parsing Json data.
 * See http://www.json.org/
 * Copyright (C) 2014 Simon Newton
 */

/**
 * @addtogroup json
 * @{
 * @file JsonParser.h
 * @brief The class used to parse JSON data.
 *
 * The implementation does it's best to conform to
 * http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-404.pdf
 * @}
 */

#ifndef INCLUDE_OLA_WEB_JSONPARSER_H_
#define INCLUDE_OLA_WEB_JSONPARSER_H_

#include <ola/web/Json.h>
#include <string>

namespace ola {
namespace web {

/**
 * @addtogroup json
 * @{
 */

/**
 * @brief Parse a string containing Json data.
 *
 * The JsonParser is actually the lexer stage. As it encounters each token in
 * the document, it calls the appropriate method on the JsonHandlerInterface.
 * It's not quite a pure lexer because it doesn't pass through tokens like ':',
 * but you get the idea.
 */
class JsonParser {
 public:
  /**
   * @brief Parse a string containing JSON data.
   * @param input the input string
   * @param handler the JsonHandlerInterface to pass tokens to.
   * @return true if parsing was successfull, false otherwise.
   */
  static bool Parse(const std::string &input,
                    class JsonHandlerInterface *handler);
};

/**
 * @brief The interface used to handle tokens during JSON parsing.
 *
 * As the JsonParser traverses the input string, it calls the methods below.
 */
class JsonHandlerInterface {
 public:
  JsonHandlerInterface() {}
  virtual ~JsonHandlerInterface() {}

  /**
   * @brief Called when parsing begins.
   */
  virtual void Begin() = 0;

  /**
   * @brief Called when parsing completes.
   */
  virtual void End() = 0;

  /**
   * @brief Called when a string is encounted.
   *
   * This is not called for object keys, see ObjectKey() below.
   */
  virtual void String(const std::string &value) = 0;

  /**
   * @brief Called when a uint32_t is encounted.
   */
  virtual void Number(uint32_t value) = 0;

  /**
   * @brief Called when a int32_t is encounted.
   */
  virtual void Number(int32_t value) = 0;

  /**
   * @brief Called when a uint64_t is encounted.
   */
  virtual void Number(uint64_t value) = 0;

  /**
   * @brief Called when a int64_t is encounted.
   */
  virtual void Number(int64_t value) = 0;

  /**
   * @brief Called when a double value is encounted.
   *
   * MinGW struggles with long doubles
   * http://mingw.5.n7.nabble.com/Strange-behaviour-of-gcc-4-8-1-with-long-double-td32949.html
   * To avoid this, and to keep as many significant bits as possible we keep
   * the components of a double separate. See JsonDoubleValue for details.
   */
  virtual void Number(const JsonDoubleValue::DoubleRepresentation &rep) = 0;

  /**
   * @brief Called when a bool is encounted.
   */
  virtual void Bool(bool value) = 0;

  /**
   * @brief Called when a null token is encounted.
   */
  virtual void Null() = 0;

  /**
   * @brief Called when an array starts.
   */
  virtual void OpenArray() = 0;

  /**
   * @brief Called when an array completes.
   */
  virtual void CloseArray() = 0;

  /**
   * @brief Called when an object starts.
   */
  virtual void OpenObject() = 0;

  /**
   * @brief Called when a new key is encounted.
   *
   * This may be called multiple times for the same object. The standard
   * doesn't specify how to handle duplicate keys, so I generally use the last
   * one.
   */
  virtual void ObjectKey(const std::string &key) = 0;

  /**
   * @brief Called when an object completes.
   */
  virtual void CloseObject() = 0;

  /**
   * @brief Can be called at any time to indicate an error with the input data.
   */
  virtual void SetError(const std::string &error) = 0;
};

/**@}*/
}  // namespace web
}  // namespace ola
#endif  // INCLUDE_OLA_WEB_JSONPARSER_H_
