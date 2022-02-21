%% Prepare workspace
close all
clear all
clc

%% setup
% portlist = serialportlist;
comPort = choose_usb_dialog();
device = serialport(comPort, 9600);


% serialData = jsonencode(9.876);

pause(2);
flush(device);

loopVal = 0;

dialogBox = uicontrol('Style', 'PushButton', 'String', 'Break','Callback', 'delete(gcbf)');
while (ishandle(dialogBox))
    disp("writing now...");

    myData.myMasterData = loopVal;
    serialData = jsonencode(myData);
    writeline(device, serialData);
    
    data = readline(device);
    try 
        decodedJson = jsondecode(data);
    catch
        decodedJson = data;
    end
    disp(decodedJson)

    loopVal = loopVal + 1;
    pause(2)
end


%%
function usbChoice = choose_usb_dialog()
    % Creates Popup to select serial port from drop-down list. 
    % Returns the usb selection as a string, usbChoice.

    % Get the list of available ports connected to the computer
    ports = cellstr(seriallist);
    
    % Prepend 'none' selection to ports cell array to allow for running
    %  the UI without a connected Arduino, FUTURE FEATURE
    ports = [{'none'},ports];
    
    d = dialog('Position',[300 300 250 150],'Name','Select Port');

    txt = uicontrol('Parent',d,...
               'Style','text',...
               'Position',[20 80 210 40],...
               'String','Select Arduino Port.'); %#ok<NASGU>
           
    popup = uicontrol('Parent',d,...
           'Style','popup',...
           'Position',[75 70 100 25],...
           'String',ports,...
           'Callback',@popup_callback); %#ok<NASGU>

    btn = uicontrol('Parent',d,...
               'Position',[85 20 70 25],...
               'String','Establish Serial',...
               'Callback','delete(gcf)'); %#ok<NASGU>
           
    % Make default selection the first cell array element
    usbChoice = ports{1};
       
    % Wait for d to close before running to completion
    uiwait(d);
   
   function popup_callback(popup,event)
      idx = popup.Value;
      popup_items = popup.String;
      % This code uses dot notation to get properties.
      % Dot notation runs in R2014b and later.
      % For R2014a and earlier:
      % idx = get(popup,'Value');
      % popup_items = get(popup,'String');
      usbChoice = char(popup_items(idx,:));
   end
end










