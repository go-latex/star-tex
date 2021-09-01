// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package fixed

import (
	"math"
	"testing"
)

func TestParseInt12_20(t *testing.T) {
	const tol = 1e-6
	for _, tc := range []struct {
		str  string
		want float64
	}{
		{"0", 0},
		{"100", 100},
		{"-100", -100},
		{"+100", +100},
		{"1.0", 1},
		{"1.2", 1.2},
		{"+1.2", +1.2},
		{"-1.2", -1.2},
	} {
		t.Run("", func(t *testing.T) {
			v, err := ParseInt12_20(tc.str)
			if err != nil {
				t.Fatalf("could not parse %q: %+v", tc.str, err)
			}
			got := v.Float64()
			if diff := math.Abs(got - tc.want); diff > tol {
				t.Fatalf("invalid 12:20 value: got=%v, want=%v (diff=%e v=%s)", got, tc.want, diff, v)
			}
		})
	}
}
