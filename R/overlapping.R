library(GenomicRanges)
library(ggplot2)

df<- as.data.frame(read.csv('../data/intervals.small.csv', dec = '.', sep = ';'))
str(df)

#epoch_time <- 1325376000
epoch_time <- 0
df$start  = df$start * 1000
df$start_time = df$start_time - epoch_time
df$start_time = df$start_time * 1000
# df$final_start_time = df$start_time + df$start

df$end  = df$end * 1000
df$end_time = df$end_time - epoch_time
df$end_time = df$end_time * 1000
# df$final_end_time = df$end_time + df$end



df$final_start_time = (df$start_time + df$start)# -epoch_time
df$final_end_time = (df$end_time + df$end) #- epoch_time


df$duration <- df$final_end_time-df$final_start_time

summary(df$duration)

min(df$duration)

granges <- GRanges(ranges = IRanges(start = df$final_start_time, end = df$final_start_time+df$duration), seqnames = 'IO', phase = as.character(df$info), job=as.character(df$filename))
granges

goverlaps <- disjoin(granges, with.revmap = TRUE)
goverlaps

plot_goverlaps <- as.data.frame(goverlaps)

plot_goverlaps$phases <- apply(plot_goverlaps, 1, function(x) {
    aux <- granges[x$revmap]$phase;
    aux <- aux[order(aux)];
    paste(unique(aux), collapse = ';')
})

plot_goverlaps$jobs <- apply(plot_goverlaps, 1, function(x) {
    aux <- granges[x$revmap]$job;
    aux <- aux[order(aux)];
    paste(unique(aux), collapse = ';');   
})

plot_goverlaps$jobs <- as.factor(plot_goverlaps$jobs)

plot_goverlaps$phases <- as.factor(plot_goverlaps$phases)

plot_goverlaps$revmap <- NULL

str(plot_goverlaps)


# ggplot(plot_goverlaps, aes()) + 
#     geom_rect(aes(xmin = start_formatted, xmax = end_formatted, ymin = 0, ymax = 1, fill=as.factor(number_of_phases))) +
#     geom_rect(aes(xmin = start_formatted, xmax = end_formatted, ymin = 1, ymax = 2, fill=as.factor(number_of_jobs))) +
#     geom_hline(yintercept = 1, linetype = 'solid', size = 0.2, color="red") +
#     geom_vline(xintercept = min(plot_goverlaps$start), linetype = 'dashed', size = 0.5) +
#     geom_vline(xintercept = max(plot_goverlaps$end), linetype = 'dashed') +
#     scale_fill_discrete(name = "filename") +
#     xlab("timestamp") +    
#     ylim(0, 2) +
#     #xlim(min(plot_goverlaps$start_formatted), max(plot_goverlaps$end_formatted) )+
#     guides(fill = guide_legend(ncol = 4)) +
#     #scale_x_continuous(breaks = seq(0, 15000, 2000)) +
#     #scale_x_datetime("", format = "%h")
#     #scale_x_datetime("",  format = "%h")+ 
#     theme_bw() +
#     theme(
#         legend.position = "none",
#         text = element_text(size = 12),
#         axis.title.y = element_blank(),
#         axis.text.y = element_blank(),
#         axis.ticks.y = element_blank()
#     )



 ggplot(plot_goverlaps, aes()) + 
    geom_rect(aes(xmin = start, xmax = start + width, ymin = 0, ymax = 1, fill=as.factor(jobs))) +
    geom_rect(aes(xmin = start, xmax = start + width, ymin = 1, ymax = 2, fill=as.factor(phases))) +
    geom_vline(xintercept = min(plot_goverlaps$start), linetype = 'dashed', size = 0.5) +
    geom_vline(xintercept = max(plot_goverlaps$end), linetype = 'dashed') +
    scale_fill_discrete(name = "Filemame \nI/O phases") +
    xlab("timestamp") +
    ylim(0, 2) +
    #xlim(min(plot_goverlaps$start), max(plot_goverlaps$end))+
    guides(fill = guide_legend(ncol = 1)) +
    #scale_x_continuous(breaks = seq(0, 15000, 2000)) +
    theme_bw() +
    theme(
        legend.position = "top",
        text = element_text(size = 12),
        axis.title.y = element_blank(),
        axis.text.y = element_blank(),
        axis.ticks.y = element_blank()
    )

ggsave("intevals.pdf", width = 6, height = 4)

