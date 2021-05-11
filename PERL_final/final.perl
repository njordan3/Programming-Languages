#!/usr/bin/perl
#Nicholas Jordan
#CMPS 3500 Final
#December 8, 2020

# RUN WITH:
#	./final.perl -h
#		(Should print the usage and exit)
#	./final.perl --csv --tab -f myStocks.csv -g stockList.csv -o output.csv
#		(Should print an error since both --csv and --tab were given and exit)
#	./final.perl --csv -f myStocks.csv -g stockList.csv -o output.csv
#	./final.perl -f myStocks.csv -g stockList.csv -o output2.csv
#	./final.perl --tab -f myStocks.dat -g stockList.dat -o output.dat
#		(Should output files of the given delimiter)

use strict;
use warnings;

# args (file, delimiter)
# returns hash where the first column from the file 
# is the key and the value is an array containing the rest
sub readFile {
	open(my $file, '<' , $_[0]) || die $!;
	my %hash;
	while (my $line = <$file>) {
		chomp $line;
		my @arr = split($_[1], $line);
		my $key = shift(@arr);
		$hash{$key} = \@arr;
	}
	close($file);
	return %hash;
}

# print string and exit
sub Error {
    print $_[0]."\n";
    exit;
}

my $personal_data = "";
my $general_info = "";
my $outfile = "";
my $csv = 0;
my $tab = 0;
my $delimiter = ",";	#default to csv
my $arg_count = @ARGV;

# parse command line
for (my $i = 0; $i < $arg_count; $i++) {
    if ($ARGV[$i] =~ /-h/) {		#help
		Error("./final.perl [-h] [--csv|--tab] -f <personal_data> -g <general_info> -o <outfile>");
    } elsif ($ARGV[$i] =~ /-f/) {	#personal data
        $i++;
        $personal_data = $ARGV[$i];
    } elsif ($ARGV[$i] =~ /-g/) {	#general info
        $i++;
        $general_info = $ARGV[$i];
    } elsif ($ARGV[$i] =~ /-o/) {	#outfile
        $i++;
        $outfile = $ARGV[$i];
    } elsif ($ARGV[$i] =~ /--csv/) {#set csv flag
        $csv = 1;
    } elsif ($ARGV[$i] =~ /--tab/) {#set dat flag
        $tab = 1;
		$delimiter = "\t";
    }
}
if ($csv == 1 and $tab == 1) {
	Error("Input files can only be of 1 type: set only 1 flag for csv or tab\n./final.perl [-h] [--csv|--tab] -f <personal_data> -g <general_info> -o <outfile>");
} elsif ($csv == 0 and $tab == 0) {
	$csv = 1;
}

if ($personal_data =~ /^$/ or $general_info =~ /^$/ or $outfile =~ /^$/) {
	Error("./final.perl [-h] [--csv|--tab] -f <personal_data> -g <general_info> -o <outfile>");
}

#each entry in the hashes stores an array
my %data;
my %info;

%data = readFile($personal_data, $delimiter);
%info = readFile($general_info, $delimiter);

print("Enter a symbol to liquidate: ");
my $sym = <STDIN>;
chomp $sym;
$sym = uc $sym;
if (exists $info{$sym}) {
	print $sym." liquidated for ".$data{$sym}[0]*$info{$sym}[0]."\n";
} else {
	print $sym." does not exist in your portfolio...\n";
}

open(OUTFILE, '>', $outfile) or die $!;
while (my $key = each (%data))
{
	my @arr1 = @{$data{$key}};	#personal data
	my @arr2 = @{$info{$key}};	#general info
	
	my @print_vals = ($arr2[1], $key, $arr1[0], $arr2[0], $arr1[0]*$arr2[0]);
	
	my $string = join($delimiter, @print_vals);
	$string =~ s/\R//g;	# get rid of ^M characters
	print OUTFILE $string."\n";
}
print "\n".$outfile." created\n";
close(OUTFILE) or die $!;
