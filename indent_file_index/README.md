Usage
===============

```
find . | sort | ./indent_file_index.py
```

and that's it.

Using prefixed flag
--------------------------------

```
find . -type d -printf "%p\tD\n" -or -type f -printf "%p\tF\n" | sort | ./indent_file_index_with_flag.py
```
