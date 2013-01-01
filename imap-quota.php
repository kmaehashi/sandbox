<?php
echo "starting...";
$mbox = imap_open("{imap.server.example.com:993/ssl}", "user"," pass",  OP_HALFOPEN)
      or die("接続できません: " . imap_last_error());
echo "connected.";

#$quota_value = imap_get_quota($mbox, "account.INBOX");
$quota = imap_get_quotaroot($mbox, "INBOX");
if (is_array($quota)) {
	print "\n\n";
	echo count($quota);
	print "\n\n";
	foreach($quota as $k => $v){
		echo $k . " ==> " . $v;
	}
   $storage = $quota['STORAGE'];
   echo "STORAGE usage level is: " .  $storage['usage'];
   echo "STORAGE limit level is: " .  $storage['limit'];

 // echo "Usage level is: " . $quota_value['usage'];
 // echo "Limit level is: " . $quota_value['limit'];
}

imap_close($mbox);
?>

