function [yfoil]=ANNBestFind(NL,NAttempt,NEpochs)
%
% NL - ����� �������� �� ������� ����
%
%
%  [ys,fs,nbits]=wavread('NOTIFY.WAV'); % Finish sound
%
% �������� �������� ������ � ���������� ��������
%
pp=load('CyMaxPat.txt');
[RP,CP]=size(pp)
%
  for ii=1:RP
  pp(ii,61)=rand;
  end   
  pps=(sortrows(pp,[61]))';
  p=pps(2:60,:);
  t=p;
%
% ������������ ������� ������
%
  [pn,minp,maxp,tn,mint,maxt] = premnmx(p,t);
%
%
  for i=1:59
   pr(i,1)=-1;
   pr(i,2)= 1;
  end
%
% �������� ��������� ���� �� ���� ���������
%
       BestError = 1000.       
%
% ������������ � �������� ��������� � ������������ ������� ��������
%
       
       for iatt = 1:NAttempt
%
% ������������  ��������� ����
%
       net = newff(pr,[59 NL 59],{'tansig' 'tansig' 'tansig'},'trainscg');
% 
       net.performFcn = 'mse';
 	    net.trainParam.show = 100;
 	    net.trainParam.goal = 1E-05;
       net.trainParam.epochs = NEpochs;
%
% �������� ����
       te.P = pn(:,401:RP);
       te.T = tn(:,401:RP);
%
       [net,tr] = train(net,pn(:,1:400),tn(:,1:400),[],[],[],te);
%
%    
%        [netCymax,tr] = train(netCymax,pn(:,1:600),tn(:,1:600),[],[],[],te);
%           
       %       
%        sound(ys,fs);
%
% ����������� ������� �������� � ������ ��� � ���� 
%        
       NetError = tr.perf(net.trainParam.epochs+1);
       Error(iatt) = NetError;
       save 'Error.txt' Error -ASCII;
%       
               if(NetError <= BestError)
                    BestError = NetError;
                    save 'BestNet.mat';
               end     
       end         
%
% �������������� ������� ��������
%
       load 'BestNet.mat'
%       
% ���������� ������ �� �������� ���� (� ������� ����� � ����������) 
%
       net.outputConnect=[0 1 0];
%
% ������������ ��������� ������� �� �������� ����
%
       outMiddleLayer = sim(net,pn);
%
% ������������ ������������� ��������� ����
%       
% ����������� ������ ��������� �������� �������
%
       [dum,mno,mxo]=premnmx(outMiddleLayer);
       prRep(:,1)=mno;       
       prRep(:,2)=mxo;
       sizeprRep = size(prRep)       
%       
% �������� ����������� ����� � ����� ������ ������ ����� ��������
% �� ������� ���� ����� "net"
%
       netRep=newff(prRep,[59],{'tansig'},'trainscg');
%
% ������������ �����
%
       netRep = init(netRep);
%
% ������� ������� ������������� � �������� ���� ����� "net" ��
% ������� ���� ����� "netRep"
%
       netRep.b{1}=net.b{3};
       netRep.IW{1}=net.LW{3,2};
%
% 
%       
       yy = sim(netRep,outMiddleLayer);
%
%
       [yfoil] = postmnmx(yy,minp,maxp);
       save 'Temp.mat';
%
