use Text::Kakasi;
use utf8;
use Encode qw/encode_utf8/;

my $txt = "庭には二羽の鶏がいる";

my $k = new Text::Kakasi;
$k->set(qw/-iutf8 -outf8 -w/);
print encode_utf8($k->get($txt)) . "\n";

