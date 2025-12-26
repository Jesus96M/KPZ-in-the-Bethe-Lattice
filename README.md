# KPZ in the Bethe Lattice

This program integrates the KPZ equation on Cayley trees (Bethe lattice).
The integration parameters—coordination number, number of layers,
equation parameters, and integration conditions—are modified in the file
`condicionesBethe.dat`.

This program is used in the article:

Numerical integration of the KPZ and related equations on networks: the case of the Cayley tree  
J. M. Marcos et al., *J. Stat. Mech.* (2025) 083203  
DOI: [10.1088/1742-5468/adf295](https://doi.org/10.1088/1742-5468/adf295)  
arXiv: https://arxiv.org/abs/2505.05311

## 🛠️ Technologies
- C

## 📦 Compilation
make

To clean generated files:  
make clean

## ▶️ Execution
./ejecutableKPZ_Bethe_RegStandard condicionesBethe.dat
