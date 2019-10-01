#!/bin/bash


if [ $# -ne 1 ]; then
    echo Usage: $0 MyNewFilter
    echo ... where MyNewFilter is the name of the filter you want to create
    exit 1
fi

filterName=$1
lowerFilterName=${filterName,,}
upperFilterName=${filterName^^}

echo Copying template...
cp -r TemplateFilter/ $filterName

echo Renaming files/directories...
for file in `find $filterName -type f -name '*templatefilter*'`;
do
    mv $file `sed s/templatefilter/$lowerFilterName/g <<< $file`;
done;

echo Renaming .pro files
for file in `find $filterName -type f -name '*.pro'`;
do
	mv $file `sed s/$lowerFilterName/$filterName/g <<< $file`;
done;

echo Renaming in files...
find $filterName -type f -exec sed -i "s/templatefilter/$lowerFilterName/g;s/TEMPLATEFILTER/$upperFilterName/g;s/TemplateFilter/$filterName/g" {} \;

echo "Done! $filterName is ready. Don't forget to add it to Filters.pro as subproject"

