function [components component1 component2 component3 component4] = principle_component(band1,band2,band3,band4)
% Find the four principle component images
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

data = [];
for i = 1 : 512
    for j = 1 : 512
        data = [data; band1(i,j) band2(i,j) band3(i,j) band4(i,j)];
    end
end

data = double(data);
covmat = cov(data)
[eig_vec eig_val] =  eig(covmat);

components = eig_vec' * data';

temp = components;
component1 = [];
component2 = [];
component3 = [];
component4 = [];

for i = 1 : 512
    data = temp(:,1:512);
    component1 = [component1; data(1,:)];
    component2 = [component2; data(2,:)];
    component3 = [component3; data(3,:)];
    component4 = [component4; data(4,:)];
    temp(:,1:512) = [];
end
    


