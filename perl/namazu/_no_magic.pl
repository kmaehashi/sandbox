# Namazu Filter to reset defualt magics provided by File::MMagic

package _no_magic;

sub mediatype() {
  return ();
}

sub status() {
  return 'no';
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
  my ($magic) = @_;
  print "Removing all magic entries...\n";
  $magic->removeSpecials();
  $magic->removeFileExts();
  return;
}

sub filter($$$$$) {
  return;
}

1;
