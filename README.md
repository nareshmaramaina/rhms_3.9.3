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
