// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package xtex

import "time"

// TimeNow is exported for tests.
var TimeNow = time.Now

func pasSysDay() int32   { return int32(TimeNow().Day()) }
func pasSysMonth() int32 { return int32(TimeNow().Month()) }
func pasSysTime() int32  { return int32(TimeNow().Hour()*60 + TimeNow().Minute()) }
func pasSysYear() int32  { return int32(TimeNow().Year()) }
