function varargout = Arduino_GUI(varargin)
% ARDUINO_GUI MATLAB code for Arduino_GUI.fig
%      ARDUINO_GUI, by itself, creates a new ARDUINO_GUI or raises the existing
%      singleton*.
%
%      H = ARDUINO_GUI returns the handle to a new ARDUINO_GUI or the handle to
%      the existing singleton*.
%
%      ARDUINO_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ARDUINO_GUI.M with the given input arguments.
%
%      ARDUINO_GUI('Property','Value',...) creates a new ARDUINO_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Arduino_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Arduino_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Arduino_GUI

% Last Modified by GUIDE v2.5 06-Apr-2020 22:50:26

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Arduino_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @Arduino_GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Arduino_GUI is made visible.
function Arduino_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Arduino_GUI (see VARARGIN)

% Choose default command line output for Arduino_GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Arduino_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% Clear Arduino
delete(instrfind({'Port'},{'COM3'}));
clear a;

global a;
a = arduino('COM3','Uno');
configurePin(a,'D8', 'Digitaloutput'); % Sets STEP pin as output
configurePin(a,'D9', 'Digitaloutput'); % Sets DIR pin as output
configurePin(a,'D13', 'Digitaloutput'); % Sets LED pin as output




% --- Outputs from this function are returned to the command line.
function varargout = Arduino_GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit_flowrate_Callback(hObject, eventdata, handles)
% hObject    handle to edit_flowrate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_flowrate as text
%        str2double(get(hObject,'String')) returns contents of edit_flowrate as a double
handles.data1 = get(hObject,'String');
handles.flowrate = str2double(handles.data1);
guidata(hObject, handles);



% --- Executes during object creation, after setting all properties.
function edit_flowrate_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_flowrate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_TubeDiameter_Callback(hObject, eventdata, handles)
% hObject    handle to edit_TubeDiameter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_TubeDiameter as text
%        str2double(get(hObject,'String')) returns contents of edit_TubeDiameter as a double
handles.data2 = get(hObject,'String');
handles.TubeDiameter = str2double(handles.data2);
guidata(hObject, handles);


% --- Executes during object creation, after setting all properties.
function edit_TubeDiameter_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_TubeDiameter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.


if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in flowrate.
function flowrate_Callback(hObject, eventdata, handles)
% hObject    handle to flowrate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global flowrate 
flowrate = handles.flowrate;

if flowrate == 0 
    handles.flowrate = 0.5;
    flowrate = handles.flowrate;
    disp('Invalid Input; Flowrate has been set to defaut 0.5 cm/s \n')
    
end

guidata(hObject, handles);

% --- Executes on button press in TubeDiameter.
function TubeDiameter_Callback(hObject, eventdata, handles)
% hObject    handle to TubeDiameter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global TubeDiameter;
TubeDiameter = handles.TubeDiameter;

if TubeDiameter == 0 
    handles.TubeDiameter = 0.3;
    TubeDiameter = handles.TubeDiameter;
    disp('Invalid Input; Tube Diameter has been set to defaut 0.3 cm/s \n')
end

guidata(hObject, handles);

% --- Executes on button press in TurnOn.
function TurnOn_Callback(hObject, eventdata, handles)
% hObject    handle to TurnOn (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
disp(handles.TubeDiameter)
disp(handles.flowrate)
 
 Area = 3.14*(handles.TubeDiameter/2)*exp(2);
 V = handles.flowrate/Area; %Tangental Vel
 S = 1.5*1.8; %Arclength of 1 motor step.
 num_step = V/S; %Number of steps per second 
 
 stepperDelay = num_step;

    global a;
    
    LEDstate = 0;
    tic % Start the timer
    LastTime = toc; % Set the last time as soon as the timer starts running
    switchtime = 1; % 0.5 seconds should be enough of a margin
    
    
    while handles.TurnOn.Value == 1
    % Turn on Stepper Motor
    writeDigitalPin(a,'D9',1); % Stepper forward function
    % Turns on Motor at a calculated stepper delay
    
    writeDigitalPin(a,'D8',1);
    pause(stepperDelay);
    writeDigitalPin(a,'D8',0);
    pause(stepperDelay);
    
    cTime = toc; % Update the current time
        if abs(cTime - LastTime) >= switchtime

            LEDstate = not(LEDstate);
            writeDigitalPin(a,'D13',LEDstate);
            lastTime = cTime;
        end
    
    end

    while handles.TurnOn.Value == 0
        writeDigitalPin(a,'D13',0);
    end
    % Turn on LED
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
