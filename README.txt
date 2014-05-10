This is a small C program written for CSI 402 at Ualbany. It is the second project for this class. This program deals with some binary files that contain information about some network packets. There are two types of packets, data packets and control packets. The control packet contains no data and contains header information, while the data packets contain only data. Both packet types have an ID and data packets also contain a payload size. The input file must be a binary file. The program is run as follow:

p2 flag input_file

The flag can be either -c, -d or -cd. The -c flag will output information about the control packets in the given input file. The -d flag will output information about the data packets in the given input file. -CD will output information about both. 

The following information is outputted about control packets:
1) The number of control packets.
2) The largest control packet ID.
3) Any missing packet IDs.

The following information is ouputted about data packets:
1) The number of data packets.
2) The largest data packet ID.
3) Any missing packet IDs.
4) The largest payload size.