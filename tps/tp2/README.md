# TP2 - Aznarez y Santoro

## pseudo-informe

#### `carga de csv`

La carga de los dos csvs se hara de la siguiente forma:

`doctores`

DOCTORES - [HASH + VECTOR] 

se leera doctor por doctor, ingresando la especialidad como clave en un hash. En el caso de que la especialidad no pertenezca al hash, se agregara al hash, y como dato habra un VECTOR que almacenara strings con el nombre de cada doctor dentro de su especialidad. 


`pacientes`

PACIENTES - [HASH]

se leera paciente por paciente, ingresandolos en un hash, usando su nombre como clave, y el anio en el que entraron a la clinica como dato. 



#### `lista de espera`

LISTA DE ESPERA - [LISTA_ESP]

Para loggear todos los pacientes vamos a usar un nuevo TDA "lista de espera" (lista_esp). Este TDA consiste en una Cola para almacenar los pacientes urgentes, y un Heap de minimos para almacenar los pacientes regulares. En el primer caso es trivial el uso de la Cola, ya que los turnos urgentes se ordenan en orden de llegada. Por otro lado, para los pacientes regulares se usa un Heap de minimos. Se elige esta estructura de datos ya que la prioridad para la asignacion del turno sera dada a partir de la antiguedad que tengan como clientes del hospital.



#### `pedir turno`

TURNOS - [HASH]

Habra otro hash de turnos con cada especialidad como clave, y como dato, una lista de espera. 

Cuando se reciba un nombre de paciente, la especialidad y la urgencia, se buscara en el hash de pacientes con su nombre. Luego se entrara al hash de turnos con la dicha especialidad, y dependiendo de su urgencia se ingresara a su respectiva estructura. 



#### `atender siguiente`

ATENDIDOS - [ABB]

Habra un ABB con strcmp de funcion de comparacion en el que se ingresara cada doctor que haya atendido a por lo menos un paciente. Se usara el nombre del Doctor como clave, y como dato la cantidad de pacientes atendidos. 



#### `informe doctores`

Se usara el ABB de atendidos para printear en orden alfabetico cada doctor con su respectivo numero de pacientes atendidos.