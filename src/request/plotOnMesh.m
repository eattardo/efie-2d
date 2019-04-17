function [Xinterp, Yinterp, Zinterp] = plotOnMesh(filename,options)

F = load(filename);

% Get x, y of the mesh
x = F(:,1);
y = F(:,2);

% Build the meshgrid
xmin = min(x);
ymin = min(y);
xmax = max(x);
ymax = max(y);
Res=length(unique(x));
xv = linspace(xmin, xmax, Res);
yv = linspace(ymin, ymax, Res);
[Xinterp,Yinterp] = meshgrid(xv,yv);

if options == 1
	Fz = abs(complex(F(:,3), F(:,4)));
	[Xi,Yi,Zinterp] = griddata(x,y,Fz,Xinterp,Yinterp);
  pcolor(Xinterp,Yinterp,Zinterp)
	axis([xmin xmax ymin ymax]),
	colormap(fire),colorbar,
	xlabel('x (m)'); ylabel('y (m)');
elseif options == 10
	Fz = abs(complex(F(:,3), F(:,4)));
  [Xi,Yi,Zinterp] = griddata(x,y,Fz,Xinterp,Yinterp);
  Zinterp = 10*log10(abs(Zinterp));
  pcolor(Xinterp,Yinterp,Zinterp)
	axis([xmin xmax ymin ymax]),
	colormap(fire),colorbar,
	xlabel('x (m)'); ylabel('y (m)');
elseif options == 11
  Fz = abs(complex(F(:,3), F(:,4)));
  [Xi,Yi,Zinterp] = griddata(x,y,Fz,Xinterp,Yinterp);  
	Zinterp = abs(Zinterp);
	%meshc(Xinterp,Yinterp,Zinterp)
	pcolor(Xinterp,Yinterp,Zinterp)
	axis([xmin xmax ymin ymax]),
	colormap(fire),colorbar,
	xlabel('x (m)'); ylabel('y (m)');
elseif options == 2
	ReChi = F(:,3);
	[Xi,Yi,ZinterpRe] = griddata(x,y,ReChi,Xinterp,Yinterp);
	ImagChi = F(:,4);
	[~,~,ZinterpIm] = griddata(x,y,ImagChi,Xinterp,Yinterp);
	% meshc(Xinterp,Yinterp,Zinterp)
	subplot(2,1,1),pcolor(Xinterp,Yinterp,ZinterpRe);
	axis([xmin xmax ymin ymax]),
	colormap(fire), colorbar,
	xlabel('x (m)'); ylabel('y (m)');
	subplot(2,1,2),pcolor(Xinterp,Yinterp,ZinterpIm);
	axis([xmin xmax ymin ymax]),
	colormap(fire), colorbar,
	xlabel('x (m)'); ylabel('y (m)');
elseif options == 3
	Epsr = F(:,3);
	[Xi,Yi,ZinterpRe] = griddata(x,y,Epsr,Xinterp,Yinterp);
	Sigma = F(:,4);
	[~,~,ZinterpIm] = griddata(x,y,Sigma,Xinterp,Yinterp);
	% meshc(Xinterp,Yinterp,Zinterp)
	subplot(2,1,1),pcolor(Xinterp,Yinterp,ZinterpRe);
	axis([xmin xmax ymin ymax]),
	colormap(fire), colorbar,
	xlabel('x (m)'); ylabel('y (m)');
	subplot(2,1,2),pcolor(Xinterp,Yinterp,ZinterpIm);
	axis([xmin xmax ymin ymax]),
	colormap(fire), colorbar,
	xlabel('x (m)'); ylabel('y (m)');
end
