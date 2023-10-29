## Build the project BOM

See  comments in `bom-merger.py` for more details.

For this project I recommend the following arguments

```bash
python bom-merger.py --hideoptional ALT --optionaltotal WLM EXTRA BSA
```



## Prepare jpg preview for markdown

To make it easier to get an idea of the project it makes sense to include images in the markdown files, but for parts that are frequently revised this will cause the size of the repository to grow. Adding the images to git-annex does not help in this regard, as then they will also not show up in the markdown documents on spaces such as GitHub. 

A compromise is to keep all images as small as reasonably possible. You can use the `make_small_jpg_preview` utility for this. It relies on `ImageMagick` being installed. I run it via WSL, but it should be possible to run it from windows too.

```shell
sh make_small_jpg_preview.sh
```

It will convert all `.png` files in the current directory into a small, compressed `.jpg`. The jpg can then be committed, while the png should not. For convenience make sure that you ignore png files in your `.gitignore`.

