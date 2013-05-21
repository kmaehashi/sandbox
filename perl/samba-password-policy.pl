#!/usr/bin/perl

# Password Policy Checker for Samba
# @author Kenichi Maehashi

chomp(my $password = <STDIN>);

sub rule($) { exit(1) if !shift; }
sub match($$) { my ($v, $p) = @_; return $v =~ m/$p/; }

# 半角 8 文字以上 100 文字以内
rule(length ($password) >= 8);
rule(length ($password) <= 100);

# 一部の記号は使用不可
rule(!match ($password, '%'));
rule(!match ($password, ','));
rule(!match ($password, '@'));
rule(!match ($password, '&'));
rule(!match ($password, '\+'));

# 2 文字以上の英字と 1 文字以上の数字を必ず使用
rule(match ($password, '[a-zA-Z](.*?)[a-zA-Z]'));
rule(match ($password, '[0-9]'));

exit(0);

