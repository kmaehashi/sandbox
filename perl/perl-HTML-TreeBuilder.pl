#!/usr/bin/perl

use HTTP::Lite;
use HTML::TreeBuilder;


sub get_title($) {
	$http = new HTTP::Lite;
	$req = $http->request($_[0]) || die $!;
	
	$body = $http->body();
	
	$tree = HTML::TreeBuilder->new;
	$tree->parse($body);
	$tree->eof();
	
	if (defined $tree->find("title")) {
		return $tree->find("title")->as_text;
	} else {
		return "";
	}
}

while(<DATA>) {
	$title = get_title($_);
	chomp($title);
	print "$title: $_\n";
}

__DATA__
http://www.youtube.com/
