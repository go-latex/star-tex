// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "plain_tex.hpp"

namespace tex {

bool 
plain::a_open_in(FILE *&ios) {
  bool found = tex::a_open_in(ios);

  if (found == false && strncmp("null.tex", name_of_file, 8) == 0) {
  	fprintf(stderr, "invalid case input-stream-buffer!!n");
  	throw std::runtime_error("boo");
    found = true;
  }

  if (found == false) {
    const std::string &absolute_path =
        input_path +
        name_of_file; // look relative to the the input directory; user macro
                      // definitions will be found there
    strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

    found = tex::a_open_in(ios);
  }

  if (found == false) {
    const std::string &absolute_path =
        output_path + name_of_file; // look in the output directory;
                                    // intermediate files will be found there
    strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

    found = tex::a_open_in(ios);
  }

  return found;
}

bool
plain::b_open_in(FILE *&ios) {
  bool found = tex::a_open_in(ios);

  if (found == false) {
    const std::string &absolute_path = input_path + name_of_file;
    strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

    found = tex::a_open_in(ios);
  }

  return found;
}

bool
plain::a_open_out(FILE *&ios) {
  std::string absolute_path = output_path + name_of_file;
  strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

  return tex::a_open_out(ios);
}

bool
plain::b_open_out(FILE *&ios) {
  std::string absolute_path = output_path + name_of_file;
  strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

  return tex::b_open_out(ios);
}

bool
plain::w_open_out(FILE *&ios) {
  std::string absolute_path = output_path + name_of_file;
  strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

  return tex::w_open_out(ios);
}

void plain::open_log_file() {
 // log_file =
 //     new std::iostream(nullptr); // we already capture the term_out as a
 //                                 // stream; a file based copy is unnecessary
}

void
plain::typeset(const std::string &filename,
		const std::string &result,
		const std::string &search_dir,
		const std::string &working_dir,
		const std::string &output) {
  input_path = search_dir;
  if (input_path.empty() == false and input_path.back() != '/')
	  input_path.push_back('/');

  output_path = working_dir;
  if (output_path.empty() == false and output_path.back() != '/')
	  output_path.push_back('/');

  input_stream = open_memstream(&input_stream_buf, &input_stream_len); // will be closed as term_in
  output_stream = fopen(output.c_str(), "w"); // will be closed as term_out

  dvi_mgr.dvi_file = fopen(result.c_str(), "w");

  tex::typeset({
		  R"(\nonstopmode)", // omits all stops (\batchmode also omits terminal
		                     // output)
		  R"(\input plain)",
		  R"(\input)",
		  filename.c_str(),
		  R"(\end)",
  });
}

} // namespace tex
