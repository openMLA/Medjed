> [!important]
>
> This repository has been rebased, making prior history unavailable in this repository. This was done as part of a move to a more scalable future for the repository, where CAD files are managed with git-annex and PCB files are in their own submodule. To get rid of the historical bloat the prior history had to be purged. It can still be accessed at [the medjed archive](https://github.com/openMLA/medjed-archive) or upon email request.



![medjed_banner](media/medjed_banner.jpg)



The **Medjed** maskless lithography aligner is part of the openMLA series of photolithography equipment. 

>  **🏗️ Construction in progress**
> A lot is still being worked on for this system. Hardware is being tested and performance will need to be evaluated before people will be able to build their own system. 

![](media/medjed_main_assembly.jpg)

### Overview

The MEDJED system is a photolithography system - this means its primary function is to expose a (flat-ish) substrate to patterened light. The substrate will need to be coated in a layer of light-sensitive material known as photoresist. This resist layer in turn will undergo chemical reactions upon exposure to UV light, either rendering areas that were exposed soluble or insoluble to a (liquid) chemical developer. After development of the exposed photoresist layer, some areas of the substrate will remain coated in the photoresist, while others will be free of it. This is the starting point for further patterning steps and is the backbone of modern microfabrication.

The MEDJED system targets a 5um pixel size in its current design. The total project cost is targeted to be 2000-2500 euro. 

There are 3 kinds of documentation for the project:

1. Documentation within this git repository. This is primarily for information about the repository contents.
2. [The project wiki](https://github.com/openMLA/Medjed/wiki). This is for a high level overview of the project, and more in-depth worked out ideas and theory.
3. [The GitHub discussions page](https://github.com/openMLA/Medjed/discussions). This is where small updates, prototypes, and failures are logged. If you have any ideas or comments, you can leave them there! 

![](media/medjed_main_assembly-alt.png)

### 🙋‍♂️Contributions

Currently the project development is in volatile waters; a lot is still changing and being tested. If you find the project very interesting and think you have some expertise in the relevant areas (e.g. optics, mechanics, machine safety, PCB design) feel free to reach out so we can see if we can divide up some tasks or if you can share some insight/critique into some of the current design layout!

If you are just interesting in trying out the system, or even just trying out some of the assemblies (e.g. just the Z-axis), your feedback and comments on the design files, practicalities and documentation are also very welcome. You can leave comments and propose new ideas in [the GitHub discussions page](https://github.com/openMLA/Medjed/discussions).

### 📃 Current component selection

Below are some of the current components selected for the machine. They may change at any point and are not necessarily the best for the job.  Still, you may find some of them interesting components for your own project.

🔗 More detailed discussion of components choices will be put in the wiki 📑.

Some highlighted components below

* XYZ axis: Snapmaker linear rails (not accurate enough for direct positioning)
* UV patterning: modified DMD projection unit from the Anycubic Photon Ultra DLP printer. See [this blog post for pictures and background](https://nemoandrea.github.io/blog/Anycubic_DLP_teardown/).
* Main optic: [Olympus Plan N 10X 0.25NA](https://www.edmundoptics.com/f/olympus-plan-achromatic-objectives/14535/).  Alternatively, [a cheaper version with the same optical design is produced in China](https://www.astroshop.eu/for-microscopes/evident-olympus-plcn10x-0-25-plan-achromat-objective/p,49913) by Olympus (part:N4239000) which should work just as well. 
* Encoders: [RLS RLC2IC magnetic encoder](https://www.rls.si/eng/rlc2ic-miniature-linear-and-rotary-pcb-level-incremental-magnetic-encoder) - 244nm spec, 2MHz
* Motion controller IC: [TMC4361A](https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC4361_Datasheet_Rev3.10.pdf)
* Microcontroller: [Teensy 4.1](https://www.pjrc.com/store/teensy41.html)
* Cameras: Raspberry Pi global shutter and HQ camera

### BOM

Consult the [BOM.csv](BOM.csv) for a  complete-ish list of components (note that it is 🏗). The BOM has optional elements.  This allows construction of cheaper versions of MEDJED if certain features are not needed. Some clarification on what the optional modules correspond to:

* WLM: White Light Module: a white light reflection microscope module that allows for inspection of sample after fabrication (image stitching and such)
* BSA: Back Side Alignment: basic camera and optics that allows for backside alignment of substrates
* EXTRA: Catch-all for nice items to have on the system (extra safety switches or extra visual indicators etc), but are not needed for any new functionality.
* ALT: components that can serve as backup for another, preferred, components in the BOM. 

The main BOM in the repository home is aggregated from subassembly BOM's. So you want to look at the components for a subassembly, simply go to the assembly and open the BOM there. [A simple utility function](utils/bom-merger.py) combines the BOMs.

### 👏 Funding Sources

The project is partially funded by the [Delft Open Hardware organisation](https://www.tudelft.nl/en/open-hardware), and the funding made available to them by the [Delft University of Technology](https://www.tudelft.nl/) for the support of open hardware development. Their support has enabled sourcing of components and has been a big enabling factor for the project development, and the project developers are grateful for their support.

### 🛠 Design Tools

Hardware parts are designed in [FreeCAD](https://www.freecad.org/)

PCBs are designed in [KiCAD](https://www.kicad.org/)

Art/Design is generated by Affinity Designer and [Inkscape](https://inkscape.org/).

