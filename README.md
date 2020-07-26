# rhms_3.9.3 is remote updating health



RHMS 

Get Config details

if Already Run
Wait for reboot 

When Hardware Changed Status Call

curl  --cacert /vision/curl-ca-bundle.crt  -XPOST -H \"content-type: application/xml\" %s/api/HardwareStatus 
curl --cacert /vision/curl-ca-bundle.crt -XPOST -H \"content-type: application/xml\" %s/api/BootTimeStatus 
curl  --cacert /vision/curl-ca-bundle.crt -XPOST -H \"content-type: application/xml\" %s/api/HealthStatus 	
