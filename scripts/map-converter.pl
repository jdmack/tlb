################################################################################
# This perl script will convert TLB map files from the old .map file format to
# to the new XML file format.
#
# Written on 2015-01-15
################################################################################

#!/usr/bin/perl
use strict;
use warnings;

my $read_file = shift;
my $write_file = shift;

my $tileset = "tiles_48.png";

# Open files for input and writing
open(IN, $read_file) || die "Cannot open file $read_file: $!";
open(OUT, ">$write_file") || die "Cannot open file $write_file: $!";

my $row = 0;
my $column = 0;
my $tile_counter = 0;

# Input map parameters
my $line = <IN>;
my @values = split(" ", $line);
my $num_of_tiles = $values[0];
my $columns = $values[1];
my $rows = $values[2];
my $width = $values[3];
my $height = $values[4];

my $tab = "    ";

print OUT "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
print OUT "<level>\n";
print OUT "$tab<tiles tileset=\"$tileset\" rows=\"$rows\" columns=\"$columns\" "
    . "width=\"$width\" height=\"$height\">\n";


while(my $line = <IN>) {
    if($line eq "\n") { next; }
    $column = 0;

    my @values = split(" ", $line);

    foreach my $value (@values) {
        $tile_counter++;
        my $type = $value + 0;
        my $x = $column * $width;
        my $y = $row * $height;
        my $walkable = "false";
        if($value eq "00" || $value eq "01" || $value eq "02") {
            $walkable = "true";
        }
        print OUT "$tab$tab<tile type=\"$type\" x=\"$x\" y=\"$y\" walkable=\"$walkable\" />\n";
        $column++;
    }

    $row++;

    if($columns != $column) {
        print "Column error on row $row - $columns/$column\n";
    }
}

if($rows != $row) {
    print "Row error - $rows/$row\n";
}

if($tile_counter != $num_of_tiles) {
    print "Error number of tiles\n";
}

print OUT "$tab</tiles>\n";
print OUT "</level>\n";

