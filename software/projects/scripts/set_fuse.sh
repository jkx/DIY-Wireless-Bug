# Set fuse for a bugOne board
# EESAVE is set
# CLOCKDIV8 is unset
avrdude -c usbasp -p m168 -U lfuse:w:0xe2:m -U hfuse:w:0xd7:m
