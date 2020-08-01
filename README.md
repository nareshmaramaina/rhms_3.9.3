# rhms_3.9.3 is remote updating health


If New details not sending it is showing as empty
RHMS 

Get Config details

if Already Run
Wait for reboot 

When Hardware Changed Status Call

curl  --cacert /vision/curl-ca-bundle.crt  -XPOST -H \"content-type: application/xml\" %s/api/HardwareStatus 
curl --cacert /vision/curl-ca-bundle.crt -XPOST -H \"content-type: application/xml\" %s/api/BootTimeStatus 
curl  --cacert /vision/curl-ca-bundle.crt -XPOST -H \"content-type: application/xml\" %s/api/HealthStatus 

Hardware Status 

<TerminalIDExists>Found<TerminalIDExists> <!-- Found/NotFound/Invalid -->
<MacidExists>Yes</Macid> <!-- Yes/Error -->
<IMEInumberExists>Yes</IMEInumberExists> <!-- Yes/Error -->
<UIDExists>Yes</UIDExists>  <!-- Yes/Error -->
<IritechSnoExists>Found</IritechSnoExists> <!-- Found/NotFound -->
<PinpadSNExists>Found</PinpadSNExists> <!-- Found/NotFound -->
<BarcodeSnoExists>F0012000000179</BarcodeSnoExists> <!-- Found/NotFound -->
<GSMVersionExists>Yes</GSMVersionExists> <!-- Yes/Error -->
<GSM_ModuleExists>Yes</GSM_ModuleExists> <!-- Yes/Error -->
<WSSNExists>Found</WSSNExists>  <!-- Found/NotFound -->
<CamTypeExists>Found</CamTypeExists> <!-- Found/NotFound -->
<FPScanneridExists>Yes</FPScanneridExists> <!-- Yes/Error -->

In Boot Status 

<SIM1CCIDnumberExists> </SIM1CCIDnumberExists>
<SIM2CCIDnumberExists>89914904900017615118</SIM2CCIDnumberExists>
<ArrayofRunningApplications>
	<Application>
		<ApplicationType>100</ApplicationType>
		<ApplicationName>100</ApplicationName>
		<ApplicationVer>3.0</ApplicationVer>
	</Application>
	<Application>
		<ApplicationType>100</ApplicationType>
		<ApplicationName>100</ApplicationName>
		<ApplicationVer>3.0</ApplicationVer>
	</Application>
</ArrayofRunningApplications>
<RHMSClientVersion>1.0</RHMSClientVersion>
<AutoapnAppVersion>1.0</AutoapnAppVersion>

In Health Status  / Periodic tags 

<FingerRDServiceStatus><FingerRDServiceStatus> <!-- Red/Blue/Green -->


As per Our discussion the newly added  tags in three requests.

In Hardware Status

<TerminalIDExists>Found</TerminalIDExists>     <!-- Found/NotFound/Invalid -->
<MacidExists>Yes</MacidExists>                         <!-- Yes/Error -->
<IMEInumberExists>Yes</IMEInumberExists>     <!-- Yes/Error -->
<UIDExists>Yes</UIDExists>                                 <!-- Yes/Error -->
<IritechSnoExists>Found</IritechSnoExists>        <!-- Found/NotFound -->
<PinpadSNExists>Found</PinpadSNExists>          <!-- Found/NotFound -->
<BarcodeSnoExists>Found</BarcodeSnoExists> <!-- Found/NotFound -->
<GSMVersionExists>Yes</GSMVersionExists> <!-- Yes/Error -->
<GSM_ModuleExists>Yes</GSM_ModuleExists> <!-- Yes/Error -->
<WSSNExists>Found</WSSNExists>  <!-- Found/NotFound -->
<CamTypeExists>Found</CamTypeExists> <!-- Found/NotFound -->
<FPScanneridExists>Yes</FPScanneridExists> <!-- Yes/Error -->

In Boot Status

<SIM1CCIDnumberExists>Yes</SIM1CCIDnumberExists> <!-- Yes/NO_SIM -->
<SIM2CCIDnumberExists>Yes</SIM2CCIDnumberExists> <!-- Yes/NO_SIM -->
<ArrayofRunningApplications>
        <Application>
                <ApplicationType>100</ApplicationType>
                <ApplicationName>100</ApplicationName>
                <ApplicationVer>3.0</ApplicationVer>
        </Application>
        <Application>
                <ApplicationType>100</ApplicationType>
                <ApplicationName>100</ApplicationName>
                <ApplicationVer>3.0</ApplicationVer>
        </Application>
</ArrayofRunningApplications>
<RHMSClientVersion>1.0</RHMSClientVersion>
<AutoapnAppVersion>1.0</AutoapnAppVersion>

In Health Status  / Periodic tags

<FingerRDServiceStatus>Red<FingerRDServiceStatus> <!-- Red/Blue/Green -->
<?xml version="1.0"?>
<DEVICE_DETAILS>
	<SerialNo>111716151423</SerialNo>
	<Date_Time>25012020123230</Date_Time>
	<TerminalID>1817161509</TerminalID>
	<Macid>7C:F0:BA:FD:C1:75</Macid>
	<UbootImageName>GL11-UB-2009.08-1410-1.0.bin</UbootImageName>
	<KernelImageName>GL11-KR-3.0.35-1411-1.0.IMG</KernelImageName>
	<RootfsImageName>GL11-RD-EXT3-1446-1.0.IMG</RootfsImageName>
	<IMEInumber>863789021521335</IMEInumber>
	<UID>2b1891d4e31731ae</UID>
	<IritechSno>F0012000000179</IritechSno>
	<PinpadSN>0012000000178457</PinpadSN>
	<BarcodeSno>F0012000000179</BarcodeSno>
	<GSMVersion>35316B09SIM5360E</GSMVersion>
	<GSM_Module>SIM5360E</GSM_Module>
	<WSSN>c8:9c:dc:32:a4:05</WSSN>
	<CamType>1f63:f001</CamType>
	<FPScannerid>A9E82A085B7520A072E3A1664214AD6F</FPScannerid>
</DEVICE_DETAILS>

<?xml version="1.0"?>
<BOOT_STATUS>
	<SerialNo>111716151423</SerialNo>
	<Date_Time>25012020123230</Date_Time>
	<DOT>
		<Date>07012019</Date>
		<Slot1>60</Slot1>
		<Slot2>200</Slot2>
		<Slot3>160</Slot3>
		<Slot4>180</Slot4>
	</DOT>
	<!-- Possible outcome: 	Connected / Not connected   -->
	<Pinpad>Connected</Pinpad>
	<Ethernet>Connected</Ethernet>
	<!-- Possible outcome:  Capacitive / Optical/ Not-Detected  -->
	<FingerPrint>Capacitive</FingerPrint>
	<!-- Possible outcome: 	 Inserted / Not Inserted -->
	<SAM1>Inserted</SAM1>
	<SAM2>Inserted</SAM2>
	<IFD1>Inserted</IFD1>
	<IFD2>Inserted</IFD2>
	<!-- Possible outcome: 	YES / No -->
	<Printer>Yes</Printer>
	<Bluetooth>YES</Bluetooth>
	<WIFI>YES</WIFI>
	<Camera>YES</Camera>
	<AUDIO>Success</AUDIO>
	<BatteryInfo>
		<Date>07012019</Date>
		<Day_worked_mins>600</Day_worked_mins>
		<Day_adapter_mins>180</Day_adapter_mins>
		<Day_charged_mins>120</Day_charged_mins>
		<Day_discharged_mins>420</Day_discharged_mins>
	</BatteryInfo>
	<ProjectID>JPDS</ProjectID>

	<ArrayofRunningApplications>
		<RHMSClientVersion></RHMSClientVersion>
		<AutoapnAppVersion></AutoapnAppVersion>

		<ArrayofApplications>
			<Application>
				<ApplicationType>100</ApplicationType>
				<ApplicationName>100</ApplicationName>
				<ApplicationVer>3.0</ApplicationVer>
			</Application>
			<Application>
				<ApplicationType>100</ApplicationType>
				<ApplicationName>100</ApplicationName>
				<ApplicationVer>3.0</ApplicationVer>
			</Application>
			<Application>
				<ApplicationType>100</ApplicationType>
				<ApplicationName>100</ApplicationName>
				<ApplicationVer>3.0</ApplicationVer>
			</Application>
		</ArrayofApplications>
		<FirmwareName>4</FirmwareName>
		<FirmwareVersion>2.4</FirmwareVersion>
		<IritechRDVer>1.0</IritechRDVer>
		<BiomRDVer>2.0</BiomRDVer>
		<FPSRDVer>1.7</FPSRDVer>
		<ExternalMem>
			<Total>3.7GB</Total>
			<Use>32.0KB</Use>
			<Free>3.7GB</Free>
		</ExternalMem>
		<ExternalMemExists>Yes</ExternalMemExists>
		<UsbdeviceExists>No</UsbdeviceExists>
		<Usbdevice>
			<Total>7.1GB</Total>
			<Use>489.0MB</Use>
			<Free>6.3GB</Free>
		</Usbdevice>
		<SIM1CCIDnumber>89914904900017615117</SIM1CCIDnumber>
		<SIM1Operator>airtel</SIM1Operator>
		<SIM2CCIDnumber>89914904900017615118</SIM2CCIDnumber>
		<SIM2Operator>idea</SIM2Operator>
	</BootStatus>
	<?xml version="1.0"?>
	<HealthStatus>
		<SerialNo>111716151423</SerialNo>
		<Date_Time>25012020123230</Date_Time>
		<GPS>
			<Latitude>17.445678</Latitude>
			<Longitude>78.465656</Longitude>
			<Captured_Time>25012020123230</Captured_Time>
		</GPS>
		<!--Possible outcome:  IRITECH or Not Connected or Biomatiques  -->
		<IRIS>IRITECH</IRIS>
		<!-- Possible outcome:  Present / Not present -->
		<PaperStatus>Present</PaperStatus>
		<!-- Possible outcome: 	Success / Failure  -->
		<RTC>Success</RTC>
		<!-- Possible outcome: 8.20V-Charged, 8.20V-Charging, 8.20V-Discharging, 0.00V-Not Connected -->
		<Battery>Connected</Battery>
		<BatteryVoltage>8.22V</BatteryVoltage>
		<Adapter>Connected</Adapter>
		<Comm>GSM</Comm>
		<SIM1db>12</SIM1db>
		<SIM2db>No</SIM2db>
		<SIM1SignalMode>3G</SIM1SignalMode>
		<SIM2SignalMode>No</SIM2SignalMode>

		<System_memory>
			<Total>1007.9M</Total>
			<Use>35.7M</Use>
			<Free>921.0M</Free>
		</System_memory>


		<InternalMem_Sysuser>
			<Total>1007.9M</Total>
			<Use>35.7M</Use>
			<Free>921.0M</Free>
		</InternalMem_Sysuser>
		<InternalMem_Jffs2>
			<Total>3.9G</Total>
			<Use>139.5M</Use>
			<Free>3.6G</Free>
		</InternalMem_Jffs2>
		<RAM>
			<Total>1008MB</Total>
			<Use>71MB</Use>
			<Free>937MB</Free>
		</RAM>
	</HealthStatus>
