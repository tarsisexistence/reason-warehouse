module DecodeArticles = {
  let article: Js.Json.t => Typings.dashboardArticle =
    json =>
      Json.Decode.{
        id: json |> field("id", string),
        author: json |> field("author", string),
        date_created: json |> field("date_created", string),
        description: json |> field("description", string),
        tags: json |> field("tags", array(string)),
        timing: json |> field("timing", int),
        title: json |> field("title", string),
      };

  let articles = Json.Decode.array(article);
};

module DecodeArticle = {
  let article: Js.Json.t => Typings.article =
    json =>
      Json.Decode.{
        id: json |> field("id", string),
        author: json |> field("author", string),
        date_created: json |> field("date_created", string),
        title: json |> field("title", string),
        timing: json |> field("timing", int),
        data: json |> field("data", string),
        date_last_modified:
          json |> field("date_last_modified", optional(string)),
        is_modified: json |> field("is_modified", bool),
        tags: json |> field("tags", array(string)),
      };
};

module Common = {
  let getMonthName = monthOrder =>
    switch (monthOrder) {
    | 0 => "January"
    | 1 => "February"
    | 2 => "March"
    | 3 => "April"
    | 4 => "May"
    | 5 => "June"
    | 6 => "July"
    | 7 => "August"
    | 8 => "September"
    | 9 => "October"
    | 10 => "November"
    | 11 => "December"
    | _ => "Never"
    };
};