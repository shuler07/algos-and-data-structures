shopt -s globstar

if [[ "$1" ]]; then
    dir="$1"
else
    dir="."
fi

if [[ ! -d "$dir" ]]; then
    echo "Directory not found"
    exit 1
fi

cd "$dir"

for file in **/Makefile*; do
    if [[ -f "$file" ]]; then
        content=$(< "$file")
        echo "${content//\\//}" > "$file"
    fi
done