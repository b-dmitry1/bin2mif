Binary file (BIN) to Quartus Memory Initialization File (MIF) format conversion tool


Usage:
bin2mif [silent] <bits> <binaryfile>

Example:
bin2mif 32 rom.bin

### Programming the device

To quickly update FPGA binaries on Windows system using Quartus 13.0sp1 located in c:\altera\13.0sp1\quartus\bin64:
* cd "path\to\quartus\project"
* c:\altera\13.0sp1\quartus\bin64\quartus_cdb (your_project_name) -c (top_level_entity_name) --update_mif
* c:\altera\13.0sp1\quartus\bin64\quartus_asm --read_settings_files=on --write_settings_files=off (your_project_name) -c (top_level_entity_name)

Example (assuming that your project located in d:\fpga\MyProject):
* d:
* cd \fpga\MyProject
* c:\altera\13.0sp1\quartus\bin64\quartus_cdb MyProject -c Main --update_mif
* c:\altera\13.0sp1\quartus\bin64\quartus_asm --read_settings_files=on --write_settings_files=off MyProject -c Main


To program your device from command line using Altera USB Blaster:
* c:\altera\13.0sp1\quartus\bin64\quartus_pgm -c usb-blaster -m JTAG -o p;output_files\Main.sof

### Compiling on Linux

To make bin2mif on Linux system:
* gcc bin2mif.c -o bin2mif

### Compiling on Windows

To make bin2mif.exe on Windows system in Visual Studio:
* Open the Native Tools (x86) command line in Visual Studio Start menu group
* Type cd "\path\to\source\folder" to change working directory
* Type "cl bin2mif.c"

Example (assuming that source located in d:\projects\bin2mif):

In the Visual Studio Native Tools command line:
* d:
* cd \projects\bin2mif
* cl bin2mif.c

### Pre-built

Pre-built executables included:
* bin2mif.exe - for Windows
* bin2mif - Linux (Ubuntu) ELF 32-bit executable (dynamic linking)
