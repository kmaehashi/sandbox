$webclient = (New-Object System.Net.WebClient)
$webclient.Encoding = [System.Text.Encoding]::GetEncoding("UTF-8")
$url = "http://jlp.yahooapis.jp/FuriganaService/V1/furigana?appid=PhoTouch&sentence=" + $args[0] + "&grade=1"
$resultXML = [xml] $webclient.DownloadString($url)
$resultXML.ResultSet.Result.WordList.Word |% {
	Write-Host -N -B DarkBlue -F White $_.Surface
	if ($_.Furigana -ne $null) {Write-Host -N -B DarkBlue -F Red ("[" + $_.Furigana + "]")}
}
Write-Host ""