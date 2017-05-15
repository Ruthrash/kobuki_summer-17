
rosinit('192.168.1.7')
chatpub = rospublisher('/goal','geometry_msgs/Twist');
msg = rosmessage(chatpub);
msg.Linear.X = 1;
msg.Linear.Y = 1; 
h = 1;
while (h ==1)
send(chatpub,msg);
%h = h+1;
end

