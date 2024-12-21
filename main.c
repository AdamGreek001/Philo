#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
   
	if (!init_simulation(argc, argv, &sim))
	{
		printf("Error: Failed to initialize simulation\n");
		return (1);
	}
	if (!start_simulation(&sim))
	{
		printf("Error: simulation failed\n");
		cleanup_simulation(&sim);
		return (1);
	}
	cleanup_simulation(&sim);
	return (0);
}
