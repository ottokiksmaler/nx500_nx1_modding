#!/usr/bin/env python3
#
# Parse and display the output of `perfman info X` and `perfman dump X`

import struct
import sys
from argparse import ArgumentParser

HDR_INFO_2 = '     Offset    Size    Name    ['
HDR_DUMP_0 = '] in memory: \n'

def c_str(val):
    """helper to convert a byte string to human readable"""
    if not val:
        return ""
    try:
        return val.decode("ascii").strip('\0')
    except UnicodeDecodeError:
        return str(val)


parser = ArgumentParser()
parser.add_argument('infofile', metavar='INFO', help='Output of `perfman info X`')
parser.add_argument('dumpfile', metavar='DUMP', help='Output of `perfman dump X`')
parser.add_argument('variable', nargs='?', default=None, help='substring match for variable names')

args = parser.parse_args()

info=open(args.infofile).readlines()
if not info[2].startswith(HDR_INFO_2):
    print(f"{args.infofile} is not a valid `perfman info` file (header mismatch in line 2)")
    sys.exit(1)

dump=open(args.dumpfile).readlines()
if not dump[0].endswith(HDR_DUMP_0):
    print(f"{args.dumpfile} is not a valid `perfman info` file (header mismatch in line 2)")
    sys.exit(1)

# remove header and footer, extract name->(offset, len)
info_data = info[4:-1]
fields = {}
for i in info_data:
    offset, length, name = i.split()
    fields[name] = (int(offset, 0), int(length, 10))

# extract byte array from dump
dump_datalines = dump[2:]
dump_hex_lines = ["".join(d.split()[1:]) for d in dump_datalines]
dump_bytes = bytes.fromhex("".join(dump_hex_lines))

for field, off_len in fields.items():
    if args.variable and not args.variable.lower() in field.lower():
        continue
    offset, length = off_len
    value = ""
    if length == 1:
        v = struct.unpack_from("<B", dump_bytes, offset=offset)[0]
        value = f"{v} (0x{v:02x})"
    elif length == 4:
        v = struct.unpack_from("<H", dump_bytes, offset=offset)[0]
        value = f"{v} (0x{v:04x})"
    elif length == 4:
        v = struct.unpack_from("<I", dump_bytes, offset=offset)[0]
        value = f"{v} (0x{v:08x})"
    else:
        v = struct.unpack_from(f"{length}s", dump_bytes, offset=offset)[0]
        value = f"'{c_str(v)}'"

    print(f"{field} (0x{offset:04x}, {length}) = {value}")
