# SSH server on the camera

Using telnet and ftp is quite okay, except for the lack of
authentication. However, it was a long-term idea to bring SSH with
SFTP and SCP to the camera. This project brings the Dropbear SSH
server and `scp` and `sftp-server` from OpenSSH to the camera, allowing
to leverage secure protocols.

## Quick install

This requires a recent version of the NX-KS mod installed to
`/opt/usr/nx-ks/`! Tested with version 2.88.

1. Copy the contents of the `files` sub-directory to your SD card.
2. Create a file `authorized_keys` with your SSH public keys on the SD card.
3. Start the camera.

This will install the binaries to `/opt/ssh` and the public keys to
`/opt/home/root/.ssh/`, and start the Dropbear SSH daemon together with
NX-KS (from `/opt/usr/nx-ks/init.sh`). Dropbear only takes ~2MB of RAM,
so it does not harm much.

On the first client connect, SSH host keys will be created and stored in
`/opt/ssh` for future use.

## Starting Dropbear

The installer will add the following to the `init.sh` file:

```shell
# start dropbear; -R = create host-keys as required
# DANGER ZONE: add -B to allow passwordless root logins
/opt/ssh/dropbear -R &
```

## Compiling the files

This requires the `sbs` toolchain that was provided by Samsung, e.g.
with the NX300 GPL source code.

### Compiling Dropbear

Download latest source from the [Dropbear Homepage](https://matt.ucc.asn.au/dropbear/dropbear.html),
tested with 2020.81; patch the paths in the source code to match the
NX1/NX500 directory structure, compile!

```shell
wget https://matt.ucc.asn.au/dropbear/releases/dropbear-2020.81.tar.bz2
tar xvjf dropbear-2020.81.tar.bz2
cd dropbear-2020.81
patch -sp1 < ../nx500_nx1_modding/ssh-server/dropbear-2020.81-nx-path.patch
./configure --host=arm-linux-gnueabi --disable-lastlog --disable-utmp --disable-wtmp \
    --disable-utmpx --disable-wtmpx --disable-zlib --disable-syslog \
    --prefix=/opt/ssh --exec-prefix=/opt/ssh
make
```

There will be a `dropbear` binary of ~240KB that you can copy to
`/opt/ssh/` on the camera.

### Compiling OpenSSH for SCP/SFTP

```shell
git clone https://github.com/openssh/openssh-portable
cd openssh-portable
autoreconf
CFLAGS="-O3 -fomit-frame-pointer -ffast-math" ./configure --host=arm-linux-gnueabi --without-zlib --without-openssl         
make -j4
```

Add the `scp` and `sftp-server` binaries from this directory to `/opt/ssh`.