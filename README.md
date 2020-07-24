# rhms_3.9.3 is remote updating health

	

		RHMS 
	
		Get Config details

		if Already Run
			Wait for reboot 

	When Hardware Changed Status Call

curl -XPOST -H "content-type: application/xml" https://rhms2.callippus.co.uk/api/HardwareChangeStatus -d @/opt/Hardware_status.xml


Every Boot Call

curl -XPOST -H "content-type: application/xml" https://rhms2.callippus.co.uk/api/FirstBootStatus -d @/opt/ BootTime_status.xml


Frequently Changed Calll

curl -XPOST -H "content-type: application/xml" https://rhms2.callippus.co.uk/api/HealthStatus -d @/opt/Health_status.xml

Regards, 	
		
