module star-tex.org/x/tex

go 1.18

retract (
	// v0.3.0 had commits missing "sign-off"
	v0.3.0

	// v0.1.x are the old CGo-based versions
	v0.1.1
	v0.1.0
)

require golang.org/x/image v0.7.0
