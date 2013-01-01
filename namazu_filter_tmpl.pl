package namazu_filter_tmpl;

sub mediatype() {
	return ('text/html');
}

sub status() {
	return 'yes';
}

sub recursive() {
	return 0;
}

sub pre_codeconv() {
	return 0;
}

sub post_codeconv() {
	return 0;
}

sub add_magic($) {
	my $magic = shift;
	return;
}

sub filter($$$$$) {
	# [IN] path to the file, [IN/OUT] ref to content of the file, [OUT] weighted string, [OUT] headings, [OUT] fields
	my ($orig_cfile, $cont, $weighted_str, $headings, $fields) = @_;
	my $data = $$cont;
	
	$$cont = "foobar" . $data;
	
	$$fields{'title'} = $title;
	
	$$weighted_str = weight($title, 16) . weight($credit, 8);
	
	return undef;	
}

# utility function (optional)
sub weight($$) {
	my ($data, $weight) = @_;
	my $W = "\x7f";
	return $W . $weight . $W . $data . $W . '/' . $weight . $W . "\n";
}

