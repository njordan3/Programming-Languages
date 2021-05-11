#!/usr/bin/perl
#Nicholas Jordan
#CMPS 3500 Lab06
#October 20, 2020

use strict;
use warnings;

# get index of max integer
sub Max {
    my @arr = @{$_[0]};
    my $size = scalar @arr;
    my $max = 0;
    for (my $i = 1; $i < $size; $i++) {
        $max = $i if ($arr[$i] > $arr[$max]);
    }
    return $max+1;
}

# print string and exit
sub Error {
    print $_[0]."\n";
    exit;
}

my $infile = "";
my $outfile = "";
my $Count = @ARGV;

# parse command line
for (my $i = 0; $i < $Count; $i++) {
    if ($ARGV[$i] =~ /-h/) {
        Error("Usage: ./lab06.perl [-h] -f <infile> -o <outfile>");
    } elsif ($ARGV[$i] =~ /-f/) {
        $i++;
        if ($ARGV[$i] =~ /-h/) {
            Error("Usage: ./lab06.perl [-h] -f <infile> -o <outfile>");    
        }
        $infile = $ARGV[$i];
    } elsif ($ARGV[$i] =~ /-o/) {
        $i++;
        if ($ARGV[$i] =~ /-h/) {
            Error("Usage: ./lab06.perl [-h] -f <infile> -o <outfile>");    
        }
        $outfile = $ARGV[$i];
    }
}

if ($infile =~ /^$/ or $outfile =~ /^$/) {
    Error("Usage: ./lab06.perl [-h] -f <infile> -o <outfile>");    
}

# 10 quiz results
my @num_correct = (0,0,0,0,0,0,0,0,0,0);
# dictionary of students
my %students;
# array of lines from the file
my @lines = ();

my $line_count = 0;
open(INFILE, $infile) or die $!;
# read and process infile contents
while(<INFILE>) {
    chomp;
    my $line = $_;

    # convert to lowercase
    $line =~ tr/A-Z/a-z/;

    # store each line in our array
    my @temp = split(',', $line);
    push(@lines, \@temp);

    # students{ ID } = name
    $students{$temp[0]} = $temp[1];

    # calculate quiz results for each line
    for (my $i = 2; $i < 12; $i++) {
        $num_correct[$i-2] += $temp[$i];
    }
    $line_count++;
}
close(INFILE);
print "Lines read: $line_count\n";

#query students
print "Enter an ID to query: ";
my $ID = <STDIN>;
chomp $ID;
if (exists $students{$ID}) {
    print "$ID is $students{$ID}.\n"
} else {
    print "NOT FOUND\n";
}

# sort array of lines by ID
my @sorted_lines = sort {$a->[0] <=> $b->[0]} @lines;

open(OUTFILE, '>', $outfile) or die $!;

print OUTFILE "Lines sorted by ID and filtered by ID with 2nd digit >= 7\n";

# log lines where ID >= 7
foreach my $row (@sorted_lines) {
    if ($row->[0] =~ /[0-9][7-9][0-9]/) {
        print OUTFILE join(',', @{$row}),"\n";
    }
}

print OUTFILE "\nCorrect Counts:\n";

my $i = 0;
foreach my $num (@num_correct) {
    $i++;
    print OUTFILE "#$i: $num   ";
}
print OUTFILE "\n";

my $max = Max(\@num_correct);

print OUTFILE "\nQuestion most answered correctly: #$max\n";

close(OUTFILE);
