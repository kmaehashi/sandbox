#!/usr/bin/env perl

use strict;
use warnings;
use Template;

my $tt = new Template;
my $vars = {
};

my $output = '';
$tt->process($ARGV[0], $vars, \$output);

print $output;
