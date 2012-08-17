#!/usr/bin/perl

my $word = $ARGV[0];
foreach (anagram($word)) {
    print $_ . "\n";
}

sub anagram($) {
    my $w = shift;
    my $l = length $w;
    my @result = ();

    if ($l <= 1) {
        @result = ($w);
    } elsif ($l == 2) { # boost up
        my $wr = reverse($w);
        @result = ($w, $wr);
    } else {
        for (my $i = 0; $i < $l; $i++) {
            my $f = substr($w, 0, 1);
            my $r = substr($w, 1);
            foreach (anagram($r)) {
                push(@result, $f . $_);
            }
            $w = $r . $f;
        }
    }
    return @result;
}

