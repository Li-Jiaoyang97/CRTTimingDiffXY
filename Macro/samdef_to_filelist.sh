# This script will take a sam definition and convert it into a file list. 
# The name of the output list will be the samdef name + _file.list
RUN=17028

#decoded-raw
for files in `samweb list-files "run_number ${RUN} and data_tier raw" ` #| grep OffBeamZero
do
  # Locate the file
  newfile=`samweb locate-file "${files}"`
  # get rid of enstore in the name
  modnewfile=${newfile#"enstore:"}
  # get rid of anything after the bracket
  modnewfile=${modnewfile%(*}
  # create the full path
  modnewfile="${modnewfile}/${files}"
  echo $modnewfile
  # Put into the new file
  ls ${modnewfile} | pnfsToXRootD >> List_run_${RUN}_OffBeamZero_file
done

echo "List_run_${RUN}_OffBeamZero_file.list CREATED"