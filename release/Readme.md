#Release directory for Otto Kiksmaler mods

What's here:
  - Modified [keyscan](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/dev/release/scripts/keyscan) that enables persistent peaking in cooperation with [OK_OK.sh](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/dev/release/scripts/OK_OK.sh) script
    - Double clicking ``OK`` button creates file (/tmp/peaking_on) that tells the keyscan program to activate focus peaking (by faking clicking on OK button) as soon as shutter button is released. To prevent silly things from happening it also switches camera to forced manual focus mode. There is still a short delay but we have to live with it for now.
    - ```keyscan``` **must** be called with ```peaking``` as one of the parameters (doesn't matter which one)
