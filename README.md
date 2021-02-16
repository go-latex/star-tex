# star-tex

[![builds.sr.ht status](https://builds.sr.ht/~sbinet/star-tex.svg)](https://builds.sr.ht/~sbinet/star-tex?)

`star-tex` (or `*TeX`) is a TeX engine in Go.

## cmd/star-tex

## cmd/tfm2pl

`tfm2pl` reads a TeX Font Metrics (TFM) file and dumps it in a human-readable text format (property-list, PL).

`tfm2pl` is a Go-based reimplementation of `TFtoPL`, distributed with TeX-live.

```
$> tfm2pl ./tfm/testdata/cmr10.tfm
(FAMILY CMR)
(FACE O 352)
(CODINGSCHEME TEX TEXT)
(DESIGNSIZE R 10.0)
(COMMENT DESIGNSIZE IS IN POINTS)
(COMMENT OTHER SIZES ARE MULTIPLES OF DESIGNSIZE)
(CHECKSUM O 11374260171)
(FONTDIMEN
   (SLANT R 0.0)
   (SPACE R 0.333334)
   (STRETCH R 0.166667)
   (SHRINK R 0.111112)
   (XHEIGHT R 0.430555)
   (QUAD R 1.000003)
   (EXTRASPACE R 0.111112)
   )
(LIGTABLE
   (LABEL O 40)
   (KRN C l R -0.277779)
   (KRN C L R -0.319446)
[...]
```
