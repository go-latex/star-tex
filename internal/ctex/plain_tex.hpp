// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_PLAIN_TEX_HPP
#define CTEX_PLAIN_TEX_HPP 1

#include "tex.hpp"

#include <string.h>
#include <stdio.h>

#include <string>


namespace tex {

class plain : public tex {

  std::string output_path;  // directory to store output files in
  std::string input_path;   // directory to search input files for

  bool a_open_in(FILE *&ios) override;
  bool b_open_in(FILE *&ios) override;
  bool a_open_out(FILE *&ios) override;
  bool b_open_out(FILE *&ios) override;
  bool w_open_out(FILE *&ios) override;
  void open_log_file() override;

public:
  virtual
  void typeset(
		  const std::string &filename,
		  const std::string &result,
		  const std::string &search_dir,
		  const std::string &working_dir,
		  const std::string &output);
};


} // namespace tex

#endif // CTEX_PLAIN_TEX_HPP

