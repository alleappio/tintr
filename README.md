# tintr

A commandline tool written in c++ that includes a mix of utilities to manage colorschemes.

Current feature list:
- Apply a colorscheme to an image
- Extract a colorscheme from an image


## Usage

Running the executable without specifying anything will get you this list of possible flags:

```
colorscheme utilities
Usage:
  tintr [OPTION...]

  -a, --apply            Apply the specified colorscheme to the input image
  -e, --extract          Extract the colorscheme from the input image
  -i, --input arg        path to the input image
  -c, --colorscheme arg  path to the colorscheme yaml file
  -o, --output arg       path in which the final image will be created 
                         (default: output.png)
  -s, --show             show results in a window
  -h, --help             print usage
```


## Colorscheme file

The colorscheme file required by the `-a` flag is simply a yaml file containing the list of colors under the `colorscheme` field, an example is provided with gruvbox in the file `colorschemes/gruvbox.yaml`.


## future development
- Right now this utility supports colorschemes only of exactly 16 colors, would be nice to be more flexible
