Creates archive from the current state using `git ls-files --cached --full-name --no-empty-directory`. Supports for any level of submodules tree. Files from submodules are extracted using the same command.

*License:* MIT

*Usage:* `git-archive-all [-v] [--prefix PREFIX] [--no-exclude] [--force-submodules] [--dry-run] OUTPUT_FILE`

*Options:*

  **--version**             Show program's version number and exit.
  
  **-h, --help**            Show this help message and exit.
  
  **--prefix=PREFIX**       Prepend PREFIX to each filename in the archive. OUTPUT_FILE name is used by default to avoid tarbomb.

  **--force-submodules**    Force a `git submodule init && git submodule update` at each level before iterating submodules
  
  **-v, --verbose**         Enable verbose mode.

  **--no-exclude**          Don't read .gitattributes files for patterns containing export-ignore attributes.

  **--dry-run**             Don't actually archive anything, just show what would be done.
