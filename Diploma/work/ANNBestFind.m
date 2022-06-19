function [yfoil]=ANNBestFind(NL,NAttempt,NEpochs)
%
% NL - число нейронов на среднем слое
%
%
%  [ys,fs,nbits]=wavread('NOTIFY.WAV'); % Finish sound
%
% загрузка исходных данных с геометрией профилей
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
% нормализация входных данных
%
  [pn,minp,maxp,tn,mint,maxt] = premnmx(p,t);
%
%
  for i=1:59
   pr(i,1)=-1;
   pr(i,2)= 1;
  end
%
% Обучение нейронной сети на всех паттернах
%
       BestError = 1000.       
%
% Формирование и обучение нейронной с запоминанием лучшего варианта
%
       
       for iatt = 1:NAttempt
%
% Формирование  нейронной сети
%
       net = newff(pr,[59 NL 59],{'tansig' 'tansig' 'tansig'},'trainscg');
% 
       net.performFcn = 'mse';
 	    net.trainParam.show = 100;
 	    net.trainParam.goal = 1E-05;
       net.trainParam.epochs = NEpochs;
%
% Обучение сети
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
% Определение лучшего варианта и запись его в файл 
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
% Восстановление лучшего варианта
%
       load 'BestNet.mat'
%       
% Добавление выхода со среднего слоя (и убираем выход с последнего) 
%
       net.outputConnect=[0 1 0];
%
% Формирование выходного массива со среднего слоя
%
       outMiddleLayer = sim(net,pn);
%
% Формирование репликативной нейронной сети
%       
% Определение границ изменения входного вектора
%
       [dum,mno,mxo]=premnmx(outMiddleLayer);
       prRep(:,1)=mno;       
       prRep(:,2)=mxo;
       sizeprRep = size(prRep)       
%       
% Создание однослойной сетки с число входов равным числу нейронов
% на среднем слое сетки "net"
%
       netRep=newff(prRep,[59],{'tansig'},'trainscg');
%
% Инициализаци сетки
%
       netRep = init(netRep);
%
% Задание весовых коэффициентов с третьего слоя сетки "net" на
% входной слой сетки "netRep"
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
